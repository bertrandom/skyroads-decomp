/* macOS / SDL2 platform layer: window, presentation, files. */
#include "compat.h"
#include <SDL.h>
#include <ctype.h>
#include <stdatomic.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <strings.h>

#define DS16(off) (*(volatile uint16_t *)(g_ds + (uint16_t)(off)))

void hw_key_event(const SDL_KeyboardEvent *k, int down);
void hw_vsync_signal(void);
void hw_mouse_motion(int dx, int dy);
void hw_mouse_buttons(int b);
void hw_joystick(int x, int y, int buttons);
int  hw_mouse_mode(void);
void hw_scancode_event(uint8_t sc, uint16_t bios, int down);

static SDL_GameController *s_pad;

/* controller -> keyboard mapping (arrows, space, enter, escape) */
static void pad_button(int button, int down)
{
    switch (button) {
        case SDL_CONTROLLER_BUTTON_DPAD_UP:    hw_scancode_event(0x48, 0x4800, down); break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:  hw_scancode_event(0x50, 0x5000, down); break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:  hw_scancode_event(0x4b, 0x4b00, down); break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: hw_scancode_event(0x4d, 0x4d00, down); break;
        case SDL_CONTROLLER_BUTTON_A:          hw_scancode_event(0x39, 0x3920, down); break;
        case SDL_CONTROLLER_BUTTON_START:      hw_scancode_event(0x1c, 0x1c0d, down); break;
        case SDL_CONTROLLER_BUTTON_B:
        case SDL_CONTROLLER_BUTTON_BACK:       hw_scancode_event(0x01, 0x011b, down); break;
        default: break;
    }
}

static void pad_axes(void)
{
    static int last[4];
    int ax, ay, i, state[4];
    if (!s_pad) return;
    ax = SDL_GameControllerGetAxis(s_pad, SDL_CONTROLLER_AXIS_LEFTX);
    ay = SDL_GameControllerGetAxis(s_pad, SDL_CONTROLLER_AXIS_LEFTY);
    hw_joystick(ax, ay, SDL_GameControllerGetButton(s_pad, SDL_CONTROLLER_BUTTON_A) |
                        (SDL_GameControllerGetButton(s_pad, SDL_CONTROLLER_BUTTON_B) << 1));
    /* analogue stick also drives the arrow keys */
    state[0] = ay < -16000; state[1] = ay > 16000; state[2] = ax < -16000; state[3] = ax > 16000;
    for (i = 0; i < 4; i++) {
        static const uint8_t sc[4] = { 0x48, 0x50, 0x4b, 0x4d };
        if (state[i] != last[i]) hw_scancode_event(sc[i], (uint16_t)(sc[i] << 8), state[i]);
        last[i] = state[i];
    }
}

static SDL_Window   *s_window;
static SDL_Renderer *s_renderer;
static SDL_Texture  *s_texture;
static int           s_scale = 3;

/* Widescreen: the original 320x200 frame in the middle, the view as wide as
 * the window (from 4:3 up to MAX_W columns, 3440x1440 ultrawide) with margins
 * either side.  During a run the margins show the road's backdrop painted out
 * to ultrawide (wide_bg.h, from backgrounds-ultrawide/filled), cut to the
 * view's width, or for a road without one, the backdrop and dashboard
 * mirrored past the frame's edges.  The intro and the menu screens show
 * their pictures painted out too (wide_menu, from menu-backgrounds/4x3/
 * filled); elsewhere the margins are black.
 * The road itself is not drawn there, so it ends at the old edges.
 * Natively: SKY_WIDE=1, or Cmd/Alt+W; the page sets the view's width. */
#include "wide_bg.h"
#define MAX_W (320 + WIDE_BG_LEFT + WIDE_BG_RIGHT)   /* 573 ~ 200 * 1.2 * 43/18 */
static int s_wide;
static int s_view_w = 320;              /* the view's width in game columns */
static int s_shown_w = -1, s_page_w;    /* what was set up; the page's choice */
static atomic_int s_in_run;
static atomic_int s_world = -1;         /* the road's backdrop, WORLDn.LZS */
static atomic_int s_menu = -1;          /* the menu screen's painted margins */

/* runtime.c: a file was opened: the road's backdrop is WORLDn.LZS; the menu
 * screens' pictures are INTRO.LZS (the intro, and the main menu, which loads
 * it again after MAINMENU.LZS), SETMENU, GOMENU and HELPMENU.LZS */
void plat_file_opened(const char *name)
{
    if (strncasecmp(name, "world", 5) == 0 && name[5] >= '0' && name[5] <= '9' &&
        strcasecmp(name + 6, ".lzs") == 0) {
        atomic_store(&s_world, name[5] - '0');
        atomic_store(&s_menu, -1);
    } else if (strcasecmp(name, "intro.lzs") == 0 || strcasecmp(name, "mainmenu.lzs") == 0)
        atomic_store(&s_menu, 0);
    else if (strcasecmp(name, "setmenu.lzs") == 0 || strcasecmp(name, "gomenu.lzs") == 0 ||
             strcasecmp(name, "helpmenu.lzs") == 0)
        atomic_store(&s_menu, 1);
}

void plat_in_run(int on) { atomic_store(&s_in_run, on); }
#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
void plat_set_wide(int on) { s_wide = on != 0; }
#ifdef __EMSCRIPTEN__
/* the page: the view's width in game columns (it sizes the canvas to fit) */
EMSCRIPTEN_KEEPALIVE void plat_set_view_width(int w) { s_page_w = w; }
EMSCRIPTEN_KEEPALIVE int plat_max_view_width(void) { return MAX_W; }
#endif

static int clamp_w(int w) { return w < 320 ? 320 : w > MAX_W ? MAX_W : w; }

/* the view's width: 320 (4:3), or in widescreen the window's shape */
static int view_width(void)
{
    if (!s_wide) return 320;
#ifdef __EMSCRIPTEN__
    return clamp_w(s_page_w ? s_page_w : 426);
#else
    {
        int ww, wh;
        const char *force = getenv("SKY_VIEW_W");   /* debug: this many columns */
        if (force && atoi(force) > 0) return clamp_w(atoi(force));
        SDL_GetWindowSize(s_window, &ww, &wh);
        return wh > 0 ? clamp_w((int)(240.0 * ww / wh + 0.5)) : 320;
    }
#endif
}

int plat_init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return -1;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
#ifdef __EMSCRIPTEN__
    /* the canvas is scaled by CSS in the page */
    s_window = SDL_CreateWindow("SkyRoads", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                320 * s_scale, 240 * s_scale, 0);
#else
    s_window = SDL_CreateWindow("SkyRoads",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                320 * s_scale, 240 * s_scale,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
#endif
    if (!s_window) return -1;
    s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_ACCELERATED |
                                    SDL_RENDERER_PRESENTVSYNC);
    if (!s_renderer) s_renderer = SDL_CreateRenderer(s_window, -1, 0);
    /* 320x200 with 4:3 aspect ratio correction (pixels are 1.2x tall) */
    SDL_RenderSetLogicalSize(s_renderer, 320, 240);
    s_texture = SDL_CreateTexture(s_renderer, SDL_PIXELFORMAT_ARGB8888,
                                  SDL_TEXTUREACCESS_STREAMING, MAX_W, 200);
    { const char *w = getenv("SKY_WIDE"); s_wide = w && *w && *w != '0'; }
    if (!s_texture) {
        fprintf(stderr, "texture: %s\n", SDL_GetError());
        return -1;
    }
    snd_init();
    return 0;
}

void plat_shutdown(void)
{
    if (s_texture)  SDL_DestroyTexture(s_texture);
    if (s_renderer) SDL_DestroyRenderer(s_renderer);
    if (s_window)   SDL_DestroyWindow(s_window);
    SDL_Quit();
}

void plat_set_palette(int first, int count, const uint8_t *rgb)
{
    int i;
    if (count <= 0) return;
    if (first < 0) first = 0;
    if (first + count > 256) count = 256 - first;
    for (i = 0; i < count; i++) {
        g_palette[first + i][0] = (uint8_t)((rgb[i * 3 + 0] & 0x3F) << 2 | (rgb[i * 3 + 0] & 0x3F) >> 4);
        g_palette[first + i][1] = (uint8_t)((rgb[i * 3 + 1] & 0x3F) << 2 | (rgb[i * 3 + 1] & 0x3F) >> 4);
        g_palette[first + i][2] = (uint8_t)((rgb[i * 3 + 2] & 0x3F) << 2 | (rgb[i * 3 + 2] & 0x3F) >> 4);
    }
}

static inline uint32_t rgb(uint8_t i)
{
    const uint8_t *c = g_palette[i];
    return 0xFF000000u | ((uint32_t)c[0] << 16) | ((uint32_t)c[1] << 8) | c[2];
}

/* the painted margins' true colours, faded with the game's palette (the
 * road fading in at a run's start and out when it ends) */
static int s_fade_now = 100;
static inline uint32_t rgb3(const unsigned char *c)
{
    uint32_t r = c[0], g = c[1], b = c[2];
    if (s_fade_now < 100) {
        r = r * (uint32_t)s_fade_now / 100;
        g = g * (uint32_t)s_fade_now / 100;
        b = b * (uint32_t)s_fade_now / 100;
    }
    return 0xFF000000u | r << 16 | g << 8 | b;
}

/* a menu screen's painted margins (wide_menu): each colour is drawn as the
 * palette index the screen's picture uses for it, through the live palette,
 * so the margins fade with the screen and cycle with the intro's road.  The
 * indices come from the screen's palette (DS:0x5182, what fades go to):
 * of the entries with the colour, the one most used on screen.  Which
 * picture: the one whose colours are all on screen (the main menu comes
 * back from Controls and Help without loading its file again), the last
 * menu file opened first, else the one with the fewest missing. */
static int menu_colours(int menu, const int *count, int *pick)
{
    const uint8_t *pal = (const uint8_t *)g_ds + 0x5182;
    int i, c, n = wide_menu_ncols[menu], missing = 0;
    for (c = 0; c < n; c++) pick[c] = -1;
    for (i = 0; i < 256; i++) {
        uint8_t r = pal[i * 3] & 63, g = pal[i * 3 + 1] & 63, b = pal[i * 3 + 2] & 63;
        unsigned char rgb[3] = { (unsigned char)(r << 2 | r >> 4), (unsigned char)(g << 2 | g >> 4),
                                 (unsigned char)(b << 2 | b >> 4) };
        for (c = 0; c < n; c++)
            if (!memcmp(rgb, wide_menu_rgb[menu][c], 3)) {
                if (pick[c] < 0 || count[i] > count[pick[c]]) pick[c] = i;
                break;
            }
    }
    for (c = 0; c < n; c++) missing += pick[c] < 0 || !count[pick[c]];   /* not on screen */
    return missing;
}

static int draw_menu_margins(uint32_t *pixels, int pitch, int left, int right)
{
    const uint8_t *fb = g_mem + VGA_BASE;
    int menu = atomic_load(&s_menu), x, y, i, c;
    int count[256], pick[64];
    uint32_t col[64];
    if (menu < 0 || !g_ds) return 0;
    for (i = 0; i < 256; i++) count[i] = 0;
    for (i = 0; i < 64000; i++) count[fb[i]]++;
    {
        int other = 1 - menu, miss = wide_menu_have[menu] ? menu_colours(menu, count, pick) : 999;
        if (miss && wide_menu_have[other] && menu_colours(other, count, pick) < miss) menu = other;
        else if (miss == 999) return 0;
        else menu_colours(menu, count, pick);
    }
    for (c = 0; c < wide_menu_ncols[menu]; c++)   /* not in the palette: as painted, faded */
        col[c] = pick[c] >= 0 ? rgb((uint8_t)pick[c]) : rgb3(wide_menu_rgb[menu][c]);
    for (y = 0; y < 200; y++) {
        uint32_t *out = (uint32_t *)((uint8_t *)pixels + y * pitch);
        const unsigned char *m = wide_menu[menu][y];
        for (x = 0; x < left; x++)  out[left - 1 - x]   = col[m[WIDE_BG_LEFT - 1 - x]];
        for (x = 0; x < right; x++) out[left + 320 + x] = col[m[WIDE_BG_LEFT + x]];
        /* the Controls backdrop is painted blending into the picture: its
         * screens' outer columns as painted too (nothing is drawn there) */
        if (menu == 1) {
            const unsigned char *e = wide_menu_edge[menu][y];
            for (x = 0; x < WIDE_BG_EDGE; x++) {
                out[left + x] = col[e[x]];
                out[left + 320 - WIDE_BG_EDGE + x] = col[e[WIDE_BG_EDGE + x]];
            }
        }
    }
    return 1;
}

/* the side margins, `left` and `right` columns: the road's painted backdrop
 * (the part nearest the frame), else the run's backdrop (DS:0x517e, the clean
 * 320x200 picture the renderer restores the road area from) mirrored at the
 * frame's edges */
static void draw_margins(uint32_t *pixels, int pitch, int left, int right)
{
    const uint8_t *bg = NULL;
    int x, y, world = atomic_load(&s_world);
    if (atomic_load(&s_in_run) && world >= 0 && wide_bg_have[world]) {
        for (y = 0; y < 200; y++) {
            uint32_t *out = (uint32_t *)((uint8_t *)pixels + y * pitch);
            const unsigned char (*m)[3] = wide_bg[world][y];
            for (x = 0; x < left; x++)
                out[left - 1 - x] = rgb3(m[WIDE_BG_LEFT - 1 - x]);
            for (x = 0; x < right; x++)
                out[left + 320 + x] = rgb3(m[WIDE_BG_LEFT + x]);
        }
        return;
    }
    if (!atomic_load(&s_in_run) && draw_menu_margins(pixels, pitch, left, right)) return;
    if (atomic_load(&s_in_run) && DS16(0x517e)) bg = g_mem + ((uint32_t)DS16(0x517e) << 4);
    for (y = 0; y < 200; y++) {
        uint32_t *out = (uint32_t *)((uint8_t *)pixels + y * pitch);
        const uint8_t *row = bg ? bg + y * 320 : NULL;
        for (x = 0; x < left; x++)  out[left - 1 - x]   = row ? rgb(row[x]) : 0xFF000000u;
        for (x = 0; x < right; x++) out[left + 320 + x] = row ? rgb(row[319 - x]) : 0xFF000000u;
    }
}

/* the frame's own outer columns, where the backdrop shows (the pixel is the
 * clean backdrop's, DS:0x517e) above the control panel, as painted: the
 * original pictures can have a dark line at their edges (Blue Planet) that
 * would stand out against the painted margins */
static void draw_frame_edges(uint32_t *frame, int pitch)
{
    int x, y, world = atomic_load(&s_world);
    const uint8_t *fb = g_mem + VGA_BASE, *bg;
    if (!atomic_load(&s_in_run) || world < 0 || !wide_bg_have[world] || !DS16(0x517e)) return;
    bg = g_mem + ((uint32_t)DS16(0x517e) << 4);
    for (y = 0; y < 129; y++) {
        uint32_t *out = (uint32_t *)((uint8_t *)frame + y * pitch);
        const unsigned char (*m)[3] = wide_bg_edge[world][y];
        for (x = 0; x < WIDE_BG_EDGE; x++) {
            int l = y * 320 + x, r = y * 320 + 320 - WIDE_BG_EDGE + x;
            if (fb[l] == bg[l]) out[x] = rgb3(m[x]);
            if (fb[r] == bg[r]) out[320 - WIDE_BG_EDGE + x] = rgb3(m[WIDE_BG_EDGE + x]);
        }
    }
}

/* the control panel painted out over the margins (rows 129-199, runs only) */
static void draw_panel_margins(uint32_t *pixels, int pitch, int left, int right)
{
    int x, y;
    if (!WIDE_PANEL_HAVE || !atomic_load(&s_in_run)) return;
    for (y = 0; y < 71; y++) {
        uint32_t *out = (uint32_t *)((uint8_t *)pixels + (129 + y) * pitch);
        const unsigned char (*m)[4] = wide_panel[y];
        for (x = 0; x < left; x++)
            if (m[WIDE_BG_LEFT - 1 - x][3]) out[left - 1 - x] = rgb3(m[WIDE_BG_LEFT - 1 - x]);
        for (x = 0; x < right; x++)
            if (m[WIDE_BG_LEFT + x][3]) out[left + 320 + x] = rgb3(m[WIDE_BG_LEFT + x]);
    }
}

static uint32_t s_shown[MAX_W * 200];   /* the last frame, for SKY_SHOT */
static int s_shot_w = 320;

void plat_present(void)
{
    void *pixels;
    int pitch;
    int w, left, right;
    SDL_Rect area;
#ifndef __EMSCRIPTEN__
    {   /* switching widescreen on or off in a window makes it 16:9 / 4:3 */
        static int shown_wide;          /* starting in widescreen (SKY_WIDE) resizes too */
        if (s_wide != shown_wide &&
            !(SDL_GetWindowFlags(s_window) & SDL_WINDOW_FULLSCREEN_DESKTOP)) {
            int ww, wh;
            SDL_GetWindowSize(s_window, &ww, &wh);
            SDL_SetWindowSize(s_window, s_wide ? wh * 16 / 9 : wh * 4 / 3, wh);
        }
        shown_wide = s_wide;
    }
#endif
    w = view_width(); left = (w - 320) / 2; right = w - 320 - left;
    area.x = area.y = 0; area.w = w; area.h = 200;
    if (w != s_shown_w) {
#ifdef __EMSCRIPTEN__
        SDL_SetWindowSize(s_window, w * s_scale, 240 * s_scale);  /* the canvas */
#endif
        s_shown_w = w;
        SDL_RenderSetLogicalSize(s_renderer, w, 240);
    }
    if (SDL_LockTexture(s_texture, &area, &pixels, &pitch) == 0) {
        const uint8_t *fb = g_mem + VGA_BASE;
        uint32_t *frame = (uint32_t *)pixels + left;
        for (int y = 0; y < 200; y++) {
            uint32_t *out = (uint32_t *)((uint8_t *)frame + y * pitch);
            const uint8_t *src = fb + y * 320;
            for (int x = 0; x < 320; x++) out[x] = rgb(src[x]);
        }
        if (w > 320) {
            s_fade_now = sky_fade_level();
            draw_frame_edges(frame, pitch);
        }
        ghost_overlay(frame, pitch);
        if (w > 320) {
            draw_margins((uint32_t *)pixels, pitch, left, right);
            if (atomic_load(&s_in_run))         /* the outer lanes past the frame */
                wide_road((uint32_t *)pixels, pitch, left, right);
            draw_panel_margins((uint32_t *)pixels, pitch, left, right);
        }
        for (int y = 0; y < 200; y++)
            memcpy(s_shown + y * w, (uint8_t *)pixels + y * pitch, (size_t)w * 4);
        s_shot_w = w;
        SDL_UnlockTexture(s_texture);
    }
    SDL_SetRenderDrawColor(s_renderer, 0, 0, 0, 255);
    SDL_RenderClear(s_renderer);
    SDL_RenderCopy(s_renderer, s_texture, &area, NULL);
    SDL_RenderPresent(s_renderer);
}

void plat_frame(void) {}
int  plat_pump_events(void) { return 1; }

/* Debug helpers: SKY_SHOT=dir saves screenshots at the times listed in
 * SKY_SHOT_AT (ms, comma separated); SKY_KEYS="ms:scancode,..." injects keys
 * (SDL scancode numbers, held for 80 ms). */
static void save_shot(const char *dir, int n)
{
    char path[512];
    SDL_Surface *s;
    SDL_Color cols[256];
    int i, y;
    if (s_shot_w > 320) {               /* the whole widescreen frame as shown */
        s = SDL_CreateRGBSurfaceWithFormatFrom(s_shown, s_shot_w, 200, 32, s_shot_w * 4,
                                               SDL_PIXELFORMAT_ARGB8888);
        snprintf(path, sizeof(path), "%s/shot%03d.bmp", dir, n);
        SDL_SaveBMP(s, path);
        SDL_FreeSurface(s);
        return;
    }
    s = SDL_CreateRGBSurfaceWithFormat(0, 320, 200, 8, SDL_PIXELFORMAT_INDEX8);
    for (i = 0; i < 256; i++) {
        cols[i].r = g_palette[i][0]; cols[i].g = g_palette[i][1];
        cols[i].b = g_palette[i][2]; cols[i].a = 255;
    }
    SDL_SetPaletteColors(s->format->palette, cols, 0, 256);
    for (y = 0; y < 200; y++)
        memcpy((uint8_t *)s->pixels + y * s->pitch, g_mem + VGA_BASE + y * 320, 320);
    snprintf(path, sizeof(path), "%s/shot%03d.bmp", dir, n);
    SDL_SaveBMP(s, path);
    SDL_FreeSurface(s);
}

/* SKY_ROAD=n (1-30): skip the intro and menus and start road n (testing):
 * Enter every 0.7 s (intro, main menu "Start!", and on the road select
 * screen (gomenu.lzs) with the road set) until the run starts. */
static void road_tick(uint64_t t)
{
    static int road = -1, start_n = -1, done;
    static uint64_t press_at = 300, release_at;
    int n;
    const char *scr;
    if (road < 0) { const char *r = getenv("SKY_ROAD"); road = r ? atoi(r) : 0; }
    if (road < 1 || road > 30 || done) return;
    if (atomic_load(&s_in_run)) { done = 1; return; }
    scr = sky_screen(&n);
    if (start_n < 0) start_n = n;
    if (press_at && t >= press_at) {
        int at_select = n != start_n && strcasecmp(scr, "gomenu.lzs") == 0;
        if (at_select) DS16(0x933e) = (uint16_t)(road - 1);
        hw_scancode_event(0x1c, 0x1c0d, 1);
        press_at = 0;
        release_at = t + 80;
    }
    if (release_at && t >= release_at) {
        hw_scancode_event(0x1c, 0x1c0d, 0);
        release_at = 0;
        press_at = t + 620;
    }
}

static void debug_tick(uint64_t t)
{
    road_tick(t);
    /* SKY_KEYS="ms:scancode[:hold_ms],..." */
    enum { MAXK = 64 };
    static int parsed, nkeys, shot_idx;
    static long k_at[MAXK], k_sc[MAXK], k_len[MAXK];
    static int k_state[MAXK];
    const char *dir = getenv("SKY_SHOT");
    const char *at = getenv("SKY_SHOT_AT");
    int i;
    if (!parsed) {
        const char *p = getenv("SKY_KEYS");
        parsed = 1;
        while (p && *p && nkeys < MAXK) {
            k_at[nkeys] = strtol(p, (char **)&p, 10);
            k_sc[nkeys] = 0; k_len[nkeys] = 80;
            if (*p == ':') { p++; k_sc[nkeys] = strtol(p, (char **)&p, 10); }
            if (*p == ':') { p++; k_len[nkeys] = strtol(p, (char **)&p, 10); }
            nkeys++;
            if (*p == ',') p++; else break;
        }
    }
    if (dir && at) {
        const char *p = at; int j = 0; long v;
        while (*p) {
            v = strtol(p, (char **)&p, 10);
            if (j == shot_idx) { if ((long)t >= v) { save_shot(dir, shot_idx); shot_idx++; } break; }
            j++; if (*p == ',') p++; else break;
        }
    }
    for (i = 0; i < nkeys; i++) {
        SDL_KeyboardEvent k;
        if (k_state[i] == 2) continue;
        if (k_state[i] == 0 && (long)t >= k_at[i]) k_state[i] = 1;
        else if (k_state[i] == 1 && (long)t >= k_at[i] + k_len[i]) k_state[i] = 3;
        else continue;
        memset(&k, 0, sizeof(k));
        k.keysym.scancode = (SDL_Scancode)k_sc[i];
        k.keysym.sym = SDL_GetKeyFromScancode((SDL_Scancode)k_sc[i]);
        hw_key_event(&k, k_state[i] == 1);
        if (k_state[i] == 3) k_state[i] = 2;
    }
}

#ifdef __EMSCRIPTEN__
/* Touch controls on the web page (main thread, like the controller above):
 * press (down=1) or release (down=0) key 0 up, 1 down, 2 left, 3 right,
 * 4 space (jump), 5 enter, 6 escape. */
EMSCRIPTEN_KEEPALIVE void sky_touch_key(int key, int down)
{
    static const uint8_t  sc[7]   = { 0x48, 0x50, 0x4b, 0x4d, 0x39, 0x1c, 0x01 };
    static const uint16_t bios[7] = { 0x4800, 0x5000, 0x4b00, 0x4d00, 0x3920, 0x1c0d, 0x011b };
    if (key >= 0 && key < 7) hw_scancode_event(sc[key], bios[key], down);
}
#endif

/* One main-thread iteration: events, input, presentation.  Returns 0 when
 * the user asked to quit. */
static int frame_step(void)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_RETURN &&
                    (e.key.keysym.mod & (KMOD_ALT | KMOD_GUI))) {
                    Uint32 fs = SDL_GetWindowFlags(s_window) & SDL_WINDOW_FULLSCREEN_DESKTOP;
                    SDL_SetWindowFullscreen(s_window, fs ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                    break;
                }
#ifndef __EMSCRIPTEN__
                if (e.key.keysym.sym == SDLK_q && (e.key.keysym.mod & KMOD_GUI))
                    return 0;
                if (e.key.keysym.sym == SDLK_w && (e.key.keysym.mod & (KMOD_ALT | KMOD_GUI))) {
                    s_wide = !s_wide;
                    break;
                }
                /* W: widescreen on/off, S: sound on/off (the game uses
                 * neither; the page has its own, see web/shell.html) */
                if (!(e.key.keysym.mod & (KMOD_CTRL | KMOD_ALT | KMOD_GUI))) {
                    if (e.key.keysym.sym == SDLK_w) {
                        if (!e.key.repeat) s_wide = !s_wide;
                        break;
                    }
                    if (e.key.keysym.sym == SDLK_s) {
                        if (!e.key.repeat) sky_set_sound(!sky_sound_on());
                        break;
                    }
                }
#endif
                hw_key_event(&e.key, 1);
                break;
            case SDL_KEYUP:
#ifndef __EMSCRIPTEN__
                if ((e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s) &&
                    !(e.key.keysym.mod & (KMOD_CTRL | KMOD_ALT | KMOD_GUI)))
                    break;
#endif
                hw_key_event(&e.key, 0);
                break;
            case SDL_MOUSEMOTION:
                if (hw_mouse_mode()) hw_mouse_motion(e.motion.xrel, e.motion.yrel);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP: {
                Uint32 st = SDL_GetMouseState(NULL, NULL);
                hw_mouse_buttons(((st & SDL_BUTTON_LMASK) ? 1 : 0) | ((st & SDL_BUTTON_RMASK) ? 2 : 0));
                break;
            }
            case SDL_CONTROLLERDEVICEADDED:
                if (!s_pad) s_pad = SDL_GameControllerOpen(e.cdevice.which);
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                if (s_pad && !SDL_GameControllerGetAttached(s_pad)) {
                    SDL_GameControllerClose(s_pad); s_pad = NULL;
                }
                break;
            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
                pad_button(e.cbutton.button, e.type == SDL_CONTROLLERBUTTONDOWN);
                break;
            default:
                break;
        }
    }
    pad_axes();
    {   /* capture the mouse only while the game uses mouse control */
        SDL_bool want = hw_mouse_mode() ? SDL_TRUE : SDL_FALSE;
        if (SDL_GetRelativeMouseMode() != want) SDL_SetRelativeMouseMode(want);
    }
    plat_present();
    hw_vsync_signal();
    debug_tick(SDL_GetTicks64());
    return 1;
}


/* path of a file in the save folder (native: the preferences folder) */
#ifndef __EMSCRIPTEN__
const char *plat_save_path(const char *file, char *buf, size_t n)
{
    char *dir = SDL_GetPrefPath("SkyRoads", "SkyRoads");
    snprintf(buf, n, "%s%s", dir ? dir : "", file);
    if (dir) SDL_free(dir);
    return buf;
}
#endif

#ifdef __EMSCRIPTEN__
static int (*s_game_done)(void);
static void (*s_start_game)(void);
static int s_started;

static void web_frame(void)
{
    if (!s_started) {
        s_started = 1;
        s_start_game();
        EM_ASM({ if (Module.onGameStarted) Module.onGameStarted(); });
    }
    frame_step();
    if (s_game_done()) {
        snd_pause();
        plat_present();
        emscripten_cancel_main_loop();
        EM_ASM({ if (Module.onGameExit) Module.onGameExit(); });
    }
}
#endif

/* Main-thread loop: events + presentation at the display refresh rate. */
void plat_run(int (*game_done)(void), void (*start_game)(void))
{
#ifdef __EMSCRIPTEN__
    s_game_done = game_done;
    s_start_game = start_game;
    emscripten_set_main_loop(web_frame, 0, 1);
#else
    uint64_t last = SDL_GetTicks64();
    start_game();
    while (!game_done()) {
        if (!frame_step()) return;
        /* if vsync is unavailable, pace at ~70 Hz like VGA mode 13h */
        {
            uint64_t now = SDL_GetTicks64();
            if (now - last < 14) SDL_Delay((Uint32)(14 - (now - last)));
            last = SDL_GetTicks64();
        }
    }
#endif
}

uint64_t plat_millis(void) { return SDL_GetTicks64(); }

/* ------------------------------------------------------------------ */
/* file access (DOS names are case-insensitive)                        */
/* ------------------------------------------------------------------ */
struct SkyFile {
    FILE  *fp;
    int    writing;
    int    cfg;         /* web: skyroads.cfg, kept as separate values */
    char  *mem;         /* in-memory contents for cfg */
    size_t memlen;
};

#ifdef __EMSCRIPTEN__
/* skyroads.cfg on the web.  The game reads and writes it as one 66-byte
 * block (DS:4516..4557; format: moddingwiki.shikadi.net/wiki/
 * SkyRoads_save_game_format):
 *     u16 checksum   sum of (controls ^ i) for i = 1..32 (the "10 02" header)
 *     u16 controls   0 keyboard, 1 joystick, 2 mouse
 *     u16 sound      0 on, otherwise off
 *     u16 roads[30]  times each road has been completed
 * The browser keeps the values themselves in localStorage instead of the
 * file: skyroads.controls ("keyboard" / "joystick" / "mouse"),
 * skyroads.sound ("on" / "off") and skyroads.roads (JSON array of 30
 * counts).  Reading the file builds the block from them; writing it stores
 * them back. */
#define CFG_SIZE  66
#define CFG_ROADS 30

static int is_cfg(const char *name) { return strcasecmp(name, "skyroads.cfg") == 0; }

static void put16(uint8_t *b, int v) { b[0] = (uint8_t)v; b[1] = (uint8_t)(v >> 8); }
static int  get16(const uint8_t *b)  { return b[0] | (b[1] << 8); }

static void cfg_build(uint8_t *b)
{
    int v[2 + CFG_ROADS], i, sum = 0;
    MAIN_THREAD_EM_ASM({
        function get(k) { try { return localStorage.getItem(k); } catch (e) { return null; } }
        var p = $0 >> 2;
        var n = $1;
        var roads = [];
        var c = ({ keyboard: 0, joystick: 1, mouse: 2 })[get('skyroads.controls')];
        HEAP32[p] = c === undefined ? 0 : c;
        HEAP32[p + 1] = get('skyroads.sound') === 'off' ? 1 : 0;
        try { roads = JSON.parse(get('skyroads.roads') || '[]'); } catch (e) {}
        if (!Array.isArray(roads)) roads = [];
        for (var i = 0; i < n; i++)
            HEAP32[p + 2 + i] = Math.max(0, Math.min(65535, roads[i] | 0));
    }, v, CFG_ROADS);
    for (i = 1; i <= 32; i++) sum += v[0] ^ i;
    put16(b, sum);
    for (i = 0; i < 2 + CFG_ROADS; i++) put16(b + 2 + i * 2, v[i]);
}

static void cfg_store(const uint8_t *b, size_t len)
{
    int v[2 + CFG_ROADS], i;
    if (len != CFG_SIZE) return;
    for (i = 0; i < 2 + CFG_ROADS; i++) v[i] = get16(b + 2 + i * 2);
    MAIN_THREAD_EM_ASM({
        var p = $0 >> 2;
        var n = $1;
        var roads = [];
        var before = [];
        for (var i = 0; i < n; i++) roads.push(HEAP32[p + 2 + i]);
        try { before = JSON.parse(localStorage.getItem('skyroads.roads') || '[]'); } catch (e) {}
        if (!Array.isArray(before)) before = [];
        /* the game saves right after counting a finished road (1000:01b8):
         * tell the page which one, for the statistics */
        if (Module.skyRoadCompleted)
            for (var r = 0; r < n; r++)
                if (roads[r] === (before[r] | 0) + 1) Module.skyRoadCompleted(r);
        try {
            localStorage.setItem('skyroads.controls', ['keyboard', 'joystick', 'mouse'][HEAP32[p]] || 'keyboard');
            localStorage.setItem('skyroads.sound', HEAP32[p + 1] ? 'off' : 'on');
            localStorage.setItem('skyroads.roads', JSON.stringify(roads));
        } catch (e) { console.warn('could not save progress', e); }
        if (Module.skySaved) Module.skySaved();     /* account sync (live-ghosts.js) */
    }, v, CFG_ROADS);
}
#endif

static FILE *open_ci(const char *name, const char *mode)
{
    char buf[256];
    size_t i, n = strlen(name);
    FILE *fp = fopen(name, mode);
    if (fp || n >= sizeof(buf)) return fp;
    for (i = 0; i <= n; i++) buf[i] = (char)toupper((unsigned char)name[i]);
    if ((fp = fopen(buf, mode))) return fp;
    for (i = 0; i <= n; i++) buf[i] = (char)tolower((unsigned char)name[i]);
    return fopen(buf, mode);
}

/* the configuration / progress file lives in the user's preferences folder */
static const char *map_name(const char *name, char *buf, size_t n)
{
#ifdef __EMSCRIPTEN__
    (void)buf; (void)n;                 /* skyroads.cfg: see cfg_build */
    return name;
#endif
    if (strcasecmp(name, "skyroads.cfg") == 0) {
        char *dir = SDL_GetPrefPath("SkyRoads", "SkyRoads");
        if (dir) { snprintf(buf, n, "%sskyroads.cfg", dir); SDL_free(dir); return buf; }
    }
    return name;
}

SkyFile *sky_open(const char *name)
{
    FILE *fp;
    char pbuf[1024];
    name = map_name(name, pbuf, sizeof pbuf);
    SkyFile *f;
    if (getenv("SKY_DEBUG")) fprintf(stderr, "[open %s]\n", name);
#ifdef __EMSCRIPTEN__
    if (is_cfg(name)) {
        f = (SkyFile *)calloc(1, sizeof(SkyFile));
        f->cfg = 1;
        f->mem = (char *)malloc(CFG_SIZE);
        cfg_build((uint8_t *)f->mem);
        f->fp = fmemopen(f->mem, CFG_SIZE, "rb");
        if (!f->fp) { free(f->mem); free(f); return NULL; }
        return f;
    }
#endif
    fp = open_ci(name, "rb");
    if (!fp) return NULL;
    f = (SkyFile *)calloc(1, sizeof(SkyFile));
    f->fp = fp;
    return f;
}
SkyFile *sky_create(const char *name)
{
    char pbuf[1024];
    FILE *fp;
    SkyFile *f;
#ifdef __EMSCRIPTEN__
    if (is_cfg(name)) {
        f = (SkyFile *)calloc(1, sizeof(SkyFile));
        f->cfg = f->writing = 1;
        f->fp = open_memstream(&f->mem, &f->memlen);
        if (!f->fp) { free(f); return NULL; }
        return f;
    }
#endif
    fp = fopen(map_name(name, pbuf, sizeof pbuf), "wb");
    if (!fp) return NULL;
    f = (SkyFile *)calloc(1, sizeof(SkyFile));
    f->fp = fp;
    f->writing = 1;
    return f;
}
int sky_read(SkyFile *f, void *dst, int len) { return (int)fread(dst, 1, len, f->fp); }
int sky_write(SkyFile *f, const void *src, int len) { return (int)fwrite(src, 1, len, f->fp); }
long sky_seek(SkyFile *f, long off, int whence)
{
    if (fseek(f->fp, off, whence == 2 ? SEEK_END : whence == 1 ? SEEK_CUR : SEEK_SET) != 0)
        return -1;
    return ftell(f->fp);
}
long sky_tell(SkyFile *f) { return ftell(f->fp); }
void sky_close(SkyFile *f)
{
    if (!f) return;
    fclose(f->fp);
#ifdef __EMSCRIPTEN__
    if (f->cfg) {
        if (f->writing) cfg_store((const uint8_t *)f->mem, f->memlen);
        free(f->mem);
        free(f);
        return;
    }
#endif
    free(f);
}
int sky_eof(SkyFile *f) { return feof(f->fp); }
