/* Ghost racers: every run of a road is recorded (ship position, height and
 * sprite per frame) and replayed as translucent ghosts at the same run time.
 *
 * Two sources:
 *  - live (browser build with a relay configured, see web/live-ghosts.js and
 *    server/relay.py): runs other players started on the same road shortly
 *    before you, streamed through a WebSocket relay.  Switching multiplayer
 *    off in the settings menu (single player) shows no ghosts; so does a
 *    browser build without a relay;
 *  - saved (native builds only): your own earlier runs of the road; the
 *    last GHOST_MAX are kept in ghosts-NN.bin in the save folder.
 *
 * Enabled by default in the browser build; natively with SKY_GHOSTS=1.
 *
 * Hooks (all on the game thread):
 *   ghost_run_begin()  1000:3b9d, called by 1000:2b3d before a run
 *   ghost_frame()      1000:0c98, once per rendered frame of a run
 *   ghost_run_end()    1000:3c03, called by 1000:2b3d after a run
 *   ghost_publish()    1000:0c98, after the frame is rendered
 * The main thread draws the current ghosts over the frame in plat_present.
 * Ghost pixels are hidden where the renderer drew a surface nearer than the
 * ghost (per-pixel road depth from render.c): block faces and tunnels by the
 * depth of their row, floor tiles by the depth of their screen line, which
 * also hides a ghost that drops into a gap.
 *
 * Ghost placement: the road is drawn with a pinhole perspective.  Fitting the
 * TREKDAT floor edges (drawn 32 lines down) gives
 *     screen_y = 9.4 + 238.5 / (2.58 + rows ahead of the ship),
 * and the ship sprite sits exactly at 0 rows ahead (its bottom line, 101,
 * is that floor line; one lane, 46 px, is the road cell width there).  A
 * ghost `dz` rows ahead of the player is drawn as the player sprite it would
 * have been, scaled by 2.58 / (2.58 + dz) towards the vanishing point
 * (160, 9.4). */
#include "compat.h"
#include "protos.h"
#include <SDL.h>
#include <stdatomic.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define DS16(off) (*(volatile uint16_t *)(g_ds + (uint16_t)(off)))
#define SEG(s)    (g_mem + ((uint32_t)(uint16_t)(s) << 4))

#define GHOST_MAX     100
#define GHOST_MAGIC   0x48475253u       /* "SRGH" */
#define GHOST_VERSION 1
#define MIN_FRAMES    36                /* ignore runs shorter than ~1 s */
#define MAX_FRAMES    60000

#define CAM_DIST   2.58f                /* camera -> ship, in rows        */
#define VP_X       160.0f               /* vanishing point                */
#define VP_Y       9.4f
#define ROAD_LINES 138                  /* road viewport (dashboard below) */
#define SPR_W 29
#define SPR_H 24

typedef struct {
    uint16_t t;         /* game ticks since the start of the run */
    uint16_t x, y;      /* 0xaf1c, 0xaf2c */
    int16_t  spr;       /* sprite index, -1 = not drawn */
    uint32_t z;         /* road position, 16.16 rows */
} Frame;

typedef struct {
    Frame   *f;
    uint32_t n;
    uint32_t cur;       /* playback cursor */
} Run;

typedef struct {
    uint32_t id;        /* relay run id */
    Frame   *f;
    uint32_t n, cap;
    uint32_t cur;
    int      ended;     /* no more frames will arrive */
    uint8_t  color;     /* tint index from the relay */
} Remote;

typedef struct {
    float   z;          /* rows ahead of the player (sort key) */
    int16_t x0, y0;     /* top left of the scaled sprite */
    float   scale;
    uint8_t alpha;      /* 0..255 */
    const uint8_t *tint;/* RGB the ghost is shaded in */
    const uint8_t *spr; /* 29x24 column-major sprite */
} Draw;

/* ghost tints: your own saved runs, and one per live player (the relay
 * gives each player shown a different index, COLORS in server/relay.py) */
static const uint8_t TINT_SAVED[3] = { 170, 215, 255 };
#define NTINTS 8
static const uint8_t TINTS[NTINTS][3] = {
    {  80, 230, 255 },  /* cyan    */
    { 255, 105, 200 },  /* pink    */
    { 255, 235,  80 },  /* yellow  */
    { 110, 255, 120 },  /* green   */
    { 255, 155,  50 },  /* orange  */
    { 175, 130, 255 },  /* violet  */
    { 255,  80,  80 },  /* red     */
    { 245, 245, 245 },  /* white   */
};

static int      s_enabled = -1;
static int      s_live;                 /* a relay is configured (browser) */
static atomic_int s_multiplayer;        /* ...and multiplayer is switched on */
static Remote   s_remote[GHOST_MAX];    /* guarded by s_lock */
static int      s_nremote;
static int      s_level = -1;           /* road whose ghosts are loaded */
static Run      s_runs[GHOST_MAX];
static int      s_nruns;

static int      s_recording;
static Frame   *s_rec;
static uint32_t s_nrec, s_caprec;
static uint32_t s_t;                    /* run clock (ticks) */
static uint32_t s_finish_t;             /* run clock at the finish, 0 = none */
static int      s_road;                 /* road of the current run */
static atomic_uint s_nonce;             /* the relay's number for this run */
void sky_sign(const char *msg, char hex[65]);   /* sign.c */
static uint16_t s_last_tick;
static int      s_first;

static SDL_mutex *s_lock;
static Draw     s_draw[GHOST_MAX];
static int      s_ndraw;
static Draw     s_player;               /* ghosts ahead are drawn behind it */
static uint8_t  s_depth[64000];         /* road depth of the shown frame    */
static float    s_floor_depth[200];     /* rows ahead of a floor line       */

/* computed by ghost_frame, shown by ghost_publish once the frame is drawn */
static Draw     s_pend[GHOST_MAX], s_pend_player;
static int      s_npend;

const char *plat_save_path(const char *file, char *buf, size_t n);

static int enabled(void)
{
    if (s_enabled < 0) {
        int y;
        s_lock = SDL_CreateMutex();
        memset(s_depth, DEPTH_NONE, sizeof s_depth);
        for (y = 0; y < 200; y++)       /* inverse of the floor perspective */
            s_floor_depth[y] = (y > VP_Y + 1) ? 238.5f / (y - VP_Y) - CAM_DIST : 1000.0f;
#ifdef __EMSCRIPTEN__
        s_enabled = 1;
#else
        const char *e = getenv("SKY_GHOSTS");
        s_enabled = e && *e && *e != '0';
#endif
    }
    return s_enabled;
}

#ifndef __EMSCRIPTEN__                  /* saved runs: native builds only */
static void free_runs(void)
{
    int i;
    for (i = 0; i < s_nruns; i++) free(s_runs[i].f);
    s_nruns = 0;
}

static const char *file_for(int level, char *buf, size_t n)
{
    char name[32];
    snprintf(name, sizeof name, "ghosts-%02d.bin", level);
    return plat_save_path(name, buf, n);
}

static void load_level(int level)
{
    char path[1024];
    FILE *fp;
    uint32_t hdr[3], i;
    free_runs();
    s_level = level;
    fp = fopen(file_for(level, path, sizeof path), "rb");
    if (!fp) return;
    if (fread(hdr, 4, 3, fp) != 3 || hdr[0] != GHOST_MAGIC || hdr[1] != GHOST_VERSION) {
        fclose(fp);
        return;
    }
    for (i = 0; i < hdr[2] && s_nruns < GHOST_MAX; i++) {
        uint32_t n;
        Frame *f;
        if (fread(&n, 4, 1, fp) != 1 || n == 0 || n > MAX_FRAMES) break;
        f = (Frame *)malloc(n * sizeof(Frame));
        if (!f) break;
        if (fread(f, sizeof(Frame), n, fp) != n) { free(f); break; }
        s_runs[s_nruns].f = f;
        s_runs[s_nruns].n = n;
        s_nruns++;
    }
    fclose(fp);
}

static void save_level(void)
{
    char path[1024];
    FILE *fp;
    uint32_t hdr[3] = { GHOST_MAGIC, GHOST_VERSION, 0 };
    int i;
    hdr[2] = (uint32_t)s_nruns;
    fp = fopen(file_for(s_level, path, sizeof path), "wb");
    if (!fp) return;
    fwrite(hdr, 4, 3, fp);
    for (i = 0; i < s_nruns; i++) {
        fwrite(&s_runs[i].n, 4, 1, fp);
        fwrite(s_runs[i].f, sizeof(Frame), s_runs[i].n, fp);
    }
    fclose(fp);
}
#endif

static void publish(const Draw *d, int n, const Draw *player, const uint8_t *depth)
{
    SDL_LockMutex(s_lock);
    if (depth) memcpy(s_depth, depth, sizeof s_depth);
    if (n) memcpy(s_draw, d, (size_t)n * sizeof(Draw));
    s_ndraw = n;
    if (player) s_player = *player;
    else s_player.spr = NULL;
    SDL_UnlockMutex(s_lock);
}

void ghost_run_begin(void)
{
    int i;
    if (!enabled()) return;
    s_recording = 0;
    if (DS16(0x95f6) == 3) { publish(NULL, 0, NULL, NULL); return; }    /* demo */
#ifdef __EMSCRIPTEN__
    {   /* with a relay configured: multiplayer (live ghosts) or, switched off
         * in the menu, single player (no ghosts); without one: no ghosts.
         * The run is followed either way so multiplayer can be switched on
         * mid-run (ghost_set_multiplayer). */
        int mode = MAIN_THREAD_EM_ASM_INT({
            if (!Module.skyGhostLive) return 0;
            return Module.skyGhostLive() ? 1 : 2;
        });
        if (mode == 0) { publish(NULL, 0, NULL, NULL); return; }
        s_live = 1;
        atomic_store(&s_multiplayer, mode == 1);
    }
#endif
    if (s_live) {
        SDL_LockMutex(s_lock);
        for (i = 0; i < s_nremote; i++) free(s_remote[i].f);
        s_nremote = 0;
        SDL_UnlockMutex(s_lock);
#ifdef __EMSCRIPTEN__
        MAIN_THREAD_ASYNC_EM_ASM({ Module.skyGhostStart($0); }, DS16(0x9332));
#endif
    }
#ifndef __EMSCRIPTEN__
    else if ((int)DS16(0x9332) != s_level) {
        load_level(DS16(0x9332));
    }
#endif
    for (i = 0; i < s_nruns; i++) s_runs[i].cur = 0;
    s_nrec = 0;
    s_t = 0;
    s_first = 1;
    s_finish_t = 0;
    s_road = DS16(0x9332);
    atomic_store(&s_nonce, 0);          /* until the relay sends this run's */
    s_recording = 1;
}

void ghost_run_end(void)
{
    if (!enabled()) return;
    s_npend = 0;
    publish(NULL, 0, NULL, NULL);
    if (!s_recording) return;
    s_recording = 0;
    if (s_live) {                               /* live runs are not saved */
#ifdef __EMSCRIPTEN__
        {   /* signed so the relay can tell the end came from the game */
            char msg[64], sig[65];
            snprintf(msg, sizeof msg, "%u|%d|%u|%u", atomic_load(&s_nonce), s_road,
                     s_t, s_finish_t);
            sky_sign(msg, sig);
            MAIN_THREAD_EM_ASM({ Module.skyGhostEnd($0, $1, UTF8ToString($2)); },
                               s_finish_t, s_t, sig);
        }
#endif
        return;
    }
#ifndef __EMSCRIPTEN__
    /* skip runs that are too short or never left the start */
    if (s_nrec < MIN_FRAMES || s_rec[s_nrec - 1].z < s_rec[0].z + 0x10000) return;
    if (s_nruns == GHOST_MAX) {                 /* drop the oldest run */
        free(s_runs[0].f);
        memmove(s_runs, s_runs + 1, (GHOST_MAX - 1) * sizeof(Run));
        s_nruns--;
    }
    s_runs[s_nruns].f = (Frame *)malloc(s_nrec * sizeof(Frame));
    if (!s_runs[s_nruns].f) return;
    memcpy(s_runs[s_nruns].f, s_rec, s_nrec * sizeof(Frame));
    s_runs[s_nruns].n = s_nrec;
    s_runs[s_nruns].cur = 0;
    s_nruns++;
    save_level();
#endif
}

/* the player sprite rectangle for a ship at x / height y (see 1000:0c98) */
static void ship_rect(uint16_t x, uint16_t y, float *left, float *top)
{
    int16_t lane = FUN_1000_0be9(x);
    *left = (float)(x / 0x80 + (int16_t)DS16(0x3e + lane * 2) - 0x6e);
    *top  = (float)(0x9d - y / 0x80);
}

static int cmp_draw(const void *a, const void *b)
{
    float za = ((const Draw *)a)->z, zb = ((const Draw *)b)->z;
    return za < zb ? 1 : za > zb ? -1 : 0;      /* far first */
}

/* Where the ghost of run `f` is at the current run time; 0 if not shown
 * (the run is over, or a live run's frames have not arrived yet). */
static int ghost_at(const Frame *f, uint32_t n, uint32_t *cur, uint32_t pz,
                    const uint8_t *tint, Draw *out)
{
    const Frame *a, *b;
    float k, gx, gy, dz, s, left, top, alpha;
    if (n == 0 || s_t > f[n - 1].t) return 0;       /* finished, or not here yet */
    while (*cur + 1 < n && f[*cur + 1].t <= s_t) (*cur)++;
    a = &f[*cur];
    if (a->t > s_t) return 0;
    b = (*cur + 1 < n) ? a + 1 : a;
    if (a->spr < 0) return 0;
    k = (b->t > a->t) ? (float)(s_t - a->t) / (float)(b->t - a->t) : 0.0f;
    gx = a->x + ((float)b->x - a->x) * k;
    gy = a->y + ((float)b->y - a->y) * k;
    dz = ((float)(int32_t)(a->z - pz) + (float)(int32_t)(b->z - a->z) * k) / 65536.0f;
    if (dz <= -1.0f || dz >= 9.0f) return 0;
    s = CAM_DIST / (CAM_DIST + dz);
    ship_rect((uint16_t)gx, (uint16_t)gy, &left, &top);
    alpha = 0.55f;
    if (dz < -0.2f) alpha *= (dz + 1.0f) / 0.8f;           /* passing the camera */
    if (dz > 7.0f)  alpha *= (9.0f - dz) / 2.0f;            /* past the road's end */
    out->z = dz;
    out->scale = s;
    out->x0 = (int16_t)(VP_X + (left - VP_X) * s + 0.5f);
    out->y0 = (int16_t)(VP_Y + (top - VP_Y) * s + 0.5f);
    out->alpha = (uint8_t)(alpha * 255.0f);
    out->tint = tint;
    out->spr = SEG(DS16(0xaf36)) + (uint16_t)(DS16(0xaf34) + a->spr * 0x2d0);
    return 1;
}

void ghost_frame(int16_t spr)
{
    Draw *d = s_pend, player;
    int nd = 0, i;
    uint16_t tick = DS16(0x1600);
    uint32_t pz;
    if (!s_recording) return;

    /* run clock: 0x1600 counts game ticks but is reset when the end-of-road
     * animation starts */
    if (s_first) s_first = 0;
    else if (tick >= s_last_tick) s_t += (uint16_t)(tick - s_last_tick);
    else {
        /* the end-of-road animation (1000:0f05) restarts the counter: the
         * road was finished here (for the fastest times) */
        if (!s_finish_t) s_finish_t = s_t;
        s_t += tick;
    }
    s_last_tick = tick;

    pz = ((uint32_t)DS16(0x961a) << 16) | DS16(0x9618);
    if (s_nrec < MAX_FRAMES && s_t <= 0xffff) {
        Frame *f;
        if (s_nrec == s_caprec) {
            uint32_t cap = s_caprec ? s_caprec * 2 : 4096;
            Frame *p = (Frame *)realloc(s_rec, cap * sizeof(Frame));
            if (!p) return;
            s_rec = p; s_caprec = cap;
        }
        f = &s_rec[s_nrec];
        if (s_nrec && s_rec[s_nrec - 1].t == (uint16_t)s_t) f--;   /* same tick */
        else s_nrec++;
        f->t = (uint16_t)s_t;
        f->x = DS16(0xaf1c);
        f->y = DS16(0xaf2c);
        f->spr = spr;
        f->z = pz;
#ifdef __EMSCRIPTEN__
        if (s_live)
            MAIN_THREAD_ASYNC_EM_ASM({ Module.skyGhostFrame($0, $1, $2, $3, $4); },
                                     f->t, f->x, f->y, f->spr, (double)f->z);
#endif
    }

    if (!s_live) {
        for (i = 0; i < s_nruns; i++)
            nd += ghost_at(s_runs[i].f, s_runs[i].n, &s_runs[i].cur, pz, TINT_SAVED, &d[nd]);
    } else if (atomic_load(&s_multiplayer)) {
        SDL_LockMutex(s_lock);
        for (i = 0; i < s_nremote; i++) {
            Remote *r = &s_remote[i];
            nd += ghost_at(r->f, r->n, &r->cur, pz, TINTS[r->color % NTINTS], &d[nd]);
        }
        SDL_UnlockMutex(s_lock);
    }
    qsort(d, (size_t)nd, sizeof(Draw), cmp_draw);
    memset(&player, 0, sizeof player);
    if (spr >= 0) {
        float left, top;
        ship_rect(DS16(0xaf1c), DS16(0xaf2c), &left, &top);
        player.x0 = (int16_t)left;
        player.y0 = (int16_t)top;
        player.spr = SEG(DS16(0xaf36)) + (uint16_t)(DS16(0xaf34) + spr * 0x2d0);
    }
    s_npend = nd;
    s_pend_player = player;
}

void ghost_publish(const uint8_t *depth)
{
    if (!s_recording) return;
    publish(s_pend, s_npend, &s_pend_player, depth);
}

/* is the road surface at (x, y) nearer than `z` rows ahead? */
static int road_hides(int x, int y, float z)
{
    uint8_t c = s_depth[y * 320 + x];
    float d;
    if (c == DEPTH_NONE) return 0;
    d = (c == DEPTH_FLOOR) ? s_floor_depth[y] : (float)c / 16.0f - 4.0f;
    return d < z - 0.3f;
}

/* is (x, y) covered by the player's ship? */
static int player_at(int x, int y)
{
    int col = x - s_player.x0, row = y - s_player.y0;
    if (!s_player.spr || col < 0 || col >= SPR_W || row < 0 || row >= SPR_H) return 0;
    return s_player.spr[col * SPR_H + row] != 0;
}

/* Main thread: blend the ghosts into the converted 320x200 frame. */
void ghost_overlay(uint32_t *pixels, int pitch)
{
    int i;
    if (s_enabled <= 0) return;
    SDL_LockMutex(s_lock);
    for (i = 0; i < s_ndraw; i++) {
        const Draw *g = &s_draw[i];
        int w = (int)(SPR_W * g->scale + 0.5f), h = (int)(SPR_H * g->scale + 0.5f);
        int sx, sy;
        uint32_t a = g->alpha;
        if (w < 1 || h < 1) continue;
        for (sy = 0; sy < h; sy++) {
            int y = g->y0 + sy, row = sy * SPR_H / h;
            uint32_t *out;
            if (y < 0 || y >= ROAD_LINES) continue;
            out = (uint32_t *)((uint8_t *)pixels + y * pitch);
            for (sx = 0; sx < w; sx++) {
                int x = g->x0 + sx, col = sx * SPR_W / w;
                uint8_t px;
                const uint8_t *c;
                uint32_t o, r, gg, b;
                if (x < 0 || x >= 320) continue;
                px = g->spr[col * SPR_H + row];
                if (!px) continue;
                if (g->z > -0.05f && player_at(x, y)) continue;  /* behind the player */
                if (road_hides(x, y, g->z)) continue;              /* behind a block */
                c = g_palette[px];
                /* the ghost's colour, shaded by the sprite's brightness,
                 * then blended over the frame */
                {
                    uint32_t lum = (c[0] * 77u + c[1] * 150u + c[2] * 29u) >> 8;
                    uint32_t shade = 115u + lum * 140u / 255u;      /* 0..255 */
                    r  = g->tint[0] * shade / 255u;
                    gg = g->tint[1] * shade / 255u;
                    b  = g->tint[2] * shade / 255u;
                }
                o = out[x];
                r  = (r  * a + ((o >> 16) & 0xff) * (255 - a)) / 255;
                gg = (gg * a + ((o >> 8)  & 0xff) * (255 - a)) / 255;
                b  = (b  * a + (o & 0xff)         * (255 - a)) / 255;
                out[x] = 0xFF000000u | (r << 16) | (gg << 8) | b;
            }
        }
    }
    SDL_UnlockMutex(s_lock);
}

/* ------------------------------------------------------------------ */
/* live ghosts: called on the main thread by web/live-ghosts.js        */
/* ------------------------------------------------------------------ */
#ifdef __EMSCRIPTEN__
static Remote *remote_get(uint32_t id)
{
    int i;
    for (i = 0; i < s_nremote; i++)
        if (s_remote[i].id == id) return &s_remote[i];
    if (s_nremote == GHOST_MAX) {               /* drop the oldest */
        free(s_remote[0].f);
        memmove(s_remote, s_remote + 1, (GHOST_MAX - 1) * sizeof(Remote));
        s_nremote--;
    }
    memset(&s_remote[s_nremote], 0, sizeof(Remote));
    s_remote[s_nremote].id = id;
    return &s_remote[s_nremote++];
}

/* append frames of relay run `id`: `n` packed 12-byte frames at `data` */
EMSCRIPTEN_KEEPALIVE void ghost_remote_frames(uint32_t id, const uint8_t *data, int n)
{
    Remote *r;
    int i;
    if (s_enabled <= 0 || n <= 0) return;
    SDL_LockMutex(s_lock);
    r = remote_get(id);
    if (r->n + (uint32_t)n > MAX_FRAMES) n = (int)(MAX_FRAMES - r->n);
    if (n > 0 && r->n + (uint32_t)n > r->cap) {
        uint32_t cap = r->cap ? r->cap : 1024;
        Frame *p;
        while (cap < r->n + (uint32_t)n) cap *= 2;
        p = (Frame *)realloc(r->f, cap * sizeof(Frame));
        if (!p) n = 0;
        else { r->f = p; r->cap = cap; }
    }
    for (i = 0; i < n; i++) {
        const uint8_t *b = data + i * 12;
        Frame *f = &r->f[r->n];
        f->t   = (uint16_t)(b[0] | b[1] << 8);
        f->x   = (uint16_t)(b[2] | b[3] << 8);
        f->y   = (uint16_t)(b[4] | b[5] << 8);
        f->spr = (int16_t)(b[6] | b[7] << 8);
        f->z   = (uint32_t)b[8] | (uint32_t)b[9] << 8 | (uint32_t)b[10] << 16 | (uint32_t)b[11] << 24;
        if (r->n && f->t < r->f[r->n - 1].t) continue;  /* keep the run ordered */
        r->n++;
    }
    SDL_UnlockMutex(s_lock);
}

EMSCRIPTEN_KEEPALIVE void ghost_remote_color(uint32_t id, int color)
{
    if (s_enabled <= 0) return;
    SDL_LockMutex(s_lock);
    remote_get(id)->color = (uint8_t)(color < 0 ? 0 : color);
    SDL_UnlockMutex(s_lock);
}

/* the relay's number for the current run, included in the signed end */
EMSCRIPTEN_KEEPALIVE void ghost_set_nonce(uint32_t nonce)
{
    atomic_store(&s_nonce, nonce);
}

/* multiplayer switched on/off in the settings menu (takes effect now) */
EMSCRIPTEN_KEEPALIVE void ghost_set_multiplayer(int on)
{
    atomic_store(&s_multiplayer, on != 0);
}

/* multiplayer switched off: drop all live ghosts */
EMSCRIPTEN_KEEPALIVE void ghost_remote_clear(void)
{
    int i;
    if (s_enabled <= 0) return;
    SDL_LockMutex(s_lock);
    for (i = 0; i < s_nremote; i++) free(s_remote[i].f);
    s_nremote = 0;
    SDL_UnlockMutex(s_lock);
}

/* the player of relay run `id` left: stop showing it */
EMSCRIPTEN_KEEPALIVE void ghost_remote_remove(uint32_t id)
{
    int i;
    if (s_enabled <= 0) return;
    SDL_LockMutex(s_lock);
    for (i = 0; i < s_nremote; i++) {
        if (s_remote[i].id != id) continue;
        free(s_remote[i].f);
        memmove(&s_remote[i], &s_remote[i + 1], (size_t)(s_nremote - i - 1) * sizeof(Remote));
        s_nremote--;
        break;
    }
    SDL_UnlockMutex(s_lock);
}

EMSCRIPTEN_KEEPALIVE void ghost_remote_end(uint32_t id)
{
    if (s_enabled <= 0) return;
    SDL_LockMutex(s_lock);
    remote_get(id)->ended = 1;
    SDL_UnlockMutex(s_lock);
}
#endif
