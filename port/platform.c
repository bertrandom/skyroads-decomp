/* macOS / SDL2 platform layer: window, presentation, files. */
#include "compat.h"
#include <SDL.h>
#include <ctype.h>
#include <stdatomic.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <strings.h>

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
                                  SDL_TEXTUREACCESS_STREAMING, 320, 200);
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

void plat_present(void)
{
    void *pixels;
    int pitch;
    if (SDL_LockTexture(s_texture, NULL, &pixels, &pitch) == 0) {
        const uint8_t *fb = g_mem + VGA_BASE;
        for (int y = 0; y < 200; y++) {
            uint32_t *out = (uint32_t *)((uint8_t *)pixels + y * pitch);
            const uint8_t *src = fb + y * 320;
            for (int x = 0; x < 320; x++) {
                const uint8_t *c = g_palette[src[x]];
                out[x] = 0xFF000000u | ((uint32_t)c[0] << 16) |
                         ((uint32_t)c[1] << 8) | c[2];
            }
        }
        SDL_UnlockTexture(s_texture);
    }
    SDL_SetRenderDrawColor(s_renderer, 0, 0, 0, 255);
    SDL_RenderClear(s_renderer);
    SDL_RenderCopy(s_renderer, s_texture, NULL, NULL);
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
    SDL_Surface *s = SDL_CreateRGBSurfaceWithFormat(0, 320, 200, 8, SDL_PIXELFORMAT_INDEX8);
    SDL_Color cols[256];
    int i, y;
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

static void debug_tick(uint64_t t)
{
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
#endif
                hw_key_event(&e.key, 1);
                break;
            case SDL_KEYUP:
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

static atomic_int s_save_dirty;     /* a file was written: persist it */

#ifdef __EMSCRIPTEN__
static int (*s_game_done)(void);
static void (*s_start_game)(void);
static int s_started;

static void web_frame(void)
{
    if (!s_started) {
        static int announced;
        /* wait until the saved files have been loaded from IndexedDB ... */
        if (!EM_ASM_INT({ return Module.skyFsReady ? 1 : 0; })) return;
        if (!announced) {
            announced = 1;
            EM_ASM({ if (Module.onReadyToStart) Module.onReadyToStart(); });
        }
        /* ... and until the player clicks: the browser only allows audio
         * after a user gesture, so the intro starts with sound. */
        if (!EM_ASM_INT({ return Module.skyStartRequested ? 1 : 0; })) {
            plat_present();
            return;
        }
        s_started = 1;
        s_start_game();
    }
    if (atomic_exchange(&s_save_dirty, 0))
        EM_ASM({ FS.syncfs(false, function (err) { if (err) console.warn('save failed', err); }); });
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
struct SkyFile { FILE *fp; int writing; };

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
    /* /save is an IndexedDB-backed mount (see main.c) */
    if (strcasecmp(name, "skyroads.cfg") == 0) { snprintf(buf, n, "/save/skyroads.cfg"); return buf; }
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
    fp = open_ci(name, "rb");
    if (!fp) return NULL;
    f = (SkyFile *)calloc(1, sizeof(SkyFile));
    f->fp = fp;
    return f;
}
SkyFile *sky_create(const char *name)
{
    char pbuf[1024];
    FILE *fp = fopen(map_name(name, pbuf, sizeof pbuf), "wb");
    SkyFile *f;
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
    if (f->writing) atomic_store(&s_save_dirty, 1);
    free(f);
}
int sky_eof(SkyFile *f) { return feof(f->fp); }
