/* PC hardware model: timer interrupt, keyboard interrupt, vertical retrace.
 *
 * Threads:
 *   main thread  - SDL window, input events, presenting the VGA framebuffer
 *   game thread  - runs the ported game code (the "CPU")
 *   timer thread - fires the programmable interval timer interrupt (IRQ0)
 *
 * The original installs its own INT 8 (timer, ~180 Hz) and INT 9 (keyboard)
 * handlers; they are re-implemented here from the disassembly at
 * 1000:3b17 and 1000:3bcc. */
#include "compat.h"
#include <stdatomic.h>
#include <SDL.h>

#define DS16(off) (*(volatile uint16_t *)(g_ds + (off)))
#define DS8(off)  (*(volatile uint8_t  *)(g_ds + (off)))

static atomic_int s_timer_isr_on;
static atomic_int s_kbd_isr_on;
static atomic_uint s_vsync_count;
static atomic_uint s_bios_ticks;

void music_tick(void);          /* audio.c: 1000:5a55 AdLib player tick */
void speaker_set_divisor(uint16_t div);

/* ------------------------------------------------------------------ */
/* INT 8 handler (1000:3b17)                                          */
/* ------------------------------------------------------------------ */
static void timer_isr(void)
{
    uint8_t c;
    music_tick();
    c = DS8(0x3192);
    if (c == 0 || c == 5) {
        uint16_t bx, cx;
        DS16(0x1600) = (uint16_t)(DS16(0x1600) + 1);
        bx = DS16(0xbd0);
        cx = *(volatile uint16_t *)(g_ds + bx);
        if (cx != 0) DS16(0xbd0) = (uint16_t)(bx + 2);
        speaker_set_divisor((uint16_t)(cx + 2));
    }
    c--;
    if ((int8_t)c < 0) {
        c = 9;
        atomic_fetch_add(&s_bios_ticks, 1);   /* chained BIOS tick, 18.2 Hz */
    }
    DS8(0x3192) = c;
}

static int timer_thread(void *arg)
{
    const double period = 6628.0 / 1193182.0;      /* PIT divisor 0x19e4 */
    uint64_t freq = SDL_GetPerformanceFrequency();
    uint64_t start = SDL_GetPerformanceCounter();
    uint64_t done = 0;
    (void)arg;
    for (;;) {
        uint64_t now = SDL_GetPerformanceCounter();
        uint64_t due = (uint64_t)((double)(now - start) / (double)freq / period);
        if (due - done > 50) done = due - 50;       /* don't spiral after a stall */
        while (done < due) {
            if (atomic_load(&s_timer_isr_on)) timer_isr();
            else if ((done % 10) == 0) atomic_fetch_add(&s_bios_ticks, 1);
            done++;
        }
        SDL_Delay(1);
    }
    return 0;
}

uint32_t timer_ticks(void) { return atomic_load(&s_bios_ticks); }

void hw_timer_isr_install(int on) { atomic_store(&s_timer_isr_on, on); }

/* ------------------------------------------------------------------ */
/* INT 9 handler (1000:3bcc)                                          */
/* ------------------------------------------------------------------ */
static void kbd_isr(uint8_t al)
{
    uint16_t bx = 0xbd2;
    while (al != DS8(bx)) {
        bx++;
        if ((DS8(bx) & 0x7f) == 0) break;
    }
    DS8(bx) = (uint8_t)((DS8(bx) & 0x7f) | ((al & 0x80) ^ 0x80));
}

void hw_kbd_isr_install(int on) { atomic_store(&s_kbd_isr_on, on); }

/* BIOS keyboard buffer (single producer: main thread, single consumer). */
#define KEYQ 64
static uint16_t s_keyq[KEYQ];
static atomic_int s_key_r, s_key_w;

static void bios_key_push(uint16_t code)
{
    int w = atomic_load(&s_key_w);
    int n = (w + 1) % KEYQ;
    if (n == atomic_load(&s_key_r)) return;
    s_keyq[w] = code;
    atomic_store(&s_key_w, n);
}

int kb_read_key(void)
{
    int r = atomic_load(&s_key_r);
    uint16_t c;
    if (r == atomic_load(&s_key_w)) return -1;
    c = s_keyq[r];
    atomic_store(&s_key_r, (r + 1) % KEYQ);
    return c;
}

int kb_key_available(void)
{
    return atomic_load(&s_key_r) != atomic_load(&s_key_w);
}

void kb_clear(void) { atomic_store(&s_key_r, atomic_load(&s_key_w)); }

/* SDL scancode -> PC/XT set 1 scancode */
static uint8_t pc_scancode(SDL_Scancode sc)
{
    switch (sc) {
        case SDL_SCANCODE_ESCAPE: return 0x01;
        case SDL_SCANCODE_1: return 0x02; case SDL_SCANCODE_2: return 0x03;
        case SDL_SCANCODE_3: return 0x04; case SDL_SCANCODE_4: return 0x05;
        case SDL_SCANCODE_5: return 0x06; case SDL_SCANCODE_6: return 0x07;
        case SDL_SCANCODE_7: return 0x08; case SDL_SCANCODE_8: return 0x09;
        case SDL_SCANCODE_9: return 0x0a; case SDL_SCANCODE_0: return 0x0b;
        case SDL_SCANCODE_MINUS: return 0x0c; case SDL_SCANCODE_EQUALS: return 0x0d;
        case SDL_SCANCODE_BACKSPACE: return 0x0e; case SDL_SCANCODE_TAB: return 0x0f;
        case SDL_SCANCODE_Q: return 0x10; case SDL_SCANCODE_W: return 0x11;
        case SDL_SCANCODE_E: return 0x12; case SDL_SCANCODE_R: return 0x13;
        case SDL_SCANCODE_T: return 0x14; case SDL_SCANCODE_Y: return 0x15;
        case SDL_SCANCODE_U: return 0x16; case SDL_SCANCODE_I: return 0x17;
        case SDL_SCANCODE_O: return 0x18; case SDL_SCANCODE_P: return 0x19;
        case SDL_SCANCODE_RETURN: case SDL_SCANCODE_KP_ENTER: return 0x1c;
        case SDL_SCANCODE_LCTRL: case SDL_SCANCODE_RCTRL: return 0x1d;
        case SDL_SCANCODE_A: return 0x1e; case SDL_SCANCODE_S: return 0x1f;
        case SDL_SCANCODE_D: return 0x20; case SDL_SCANCODE_F: return 0x21;
        case SDL_SCANCODE_G: return 0x22; case SDL_SCANCODE_H: return 0x23;
        case SDL_SCANCODE_J: return 0x24; case SDL_SCANCODE_K: return 0x25;
        case SDL_SCANCODE_L: return 0x26;
        case SDL_SCANCODE_LSHIFT: return 0x2a; case SDL_SCANCODE_RSHIFT: return 0x36;
        case SDL_SCANCODE_Z: return 0x2c; case SDL_SCANCODE_X: return 0x2d;
        case SDL_SCANCODE_C: return 0x2e; case SDL_SCANCODE_V: return 0x2f;
        case SDL_SCANCODE_B: return 0x30; case SDL_SCANCODE_N: return 0x31;
        case SDL_SCANCODE_M: return 0x32;
        case SDL_SCANCODE_LALT: case SDL_SCANCODE_RALT: return 0x38;
        case SDL_SCANCODE_SPACE: return 0x39;
        case SDL_SCANCODE_F1: return 0x3b; case SDL_SCANCODE_F2: return 0x3c;
        case SDL_SCANCODE_F3: return 0x3d; case SDL_SCANCODE_F4: return 0x3e;
        case SDL_SCANCODE_F5: return 0x3f; case SDL_SCANCODE_F6: return 0x40;
        case SDL_SCANCODE_F7: return 0x41; case SDL_SCANCODE_F8: return 0x42;
        case SDL_SCANCODE_F9: return 0x43; case SDL_SCANCODE_F10: return 0x44;
        case SDL_SCANCODE_HOME: case SDL_SCANCODE_KP_7: return 0x47;
        case SDL_SCANCODE_UP: case SDL_SCANCODE_KP_8: return 0x48;
        case SDL_SCANCODE_PAGEUP: case SDL_SCANCODE_KP_9: return 0x49;
        case SDL_SCANCODE_LEFT: case SDL_SCANCODE_KP_4: return 0x4b;
        case SDL_SCANCODE_RIGHT: case SDL_SCANCODE_KP_6: return 0x4d;
        case SDL_SCANCODE_END: case SDL_SCANCODE_KP_1: return 0x4f;
        case SDL_SCANCODE_DOWN: case SDL_SCANCODE_KP_2: return 0x50;
        case SDL_SCANCODE_PAGEDOWN: case SDL_SCANCODE_KP_3: return 0x51;
        default: return 0;
    }
}

/* BIOS INT 16h style code: scan in high byte, ASCII in low byte. */
static uint16_t bios_code(const SDL_KeyboardEvent *k)
{
    uint8_t sc = pc_scancode(k->keysym.scancode);
    SDL_Keycode sym = k->keysym.sym;
    uint8_t ascii = 0;
    if (sym == SDLK_RETURN || sym == SDLK_KP_ENTER) ascii = 0x0d;
    else if (sym == SDLK_ESCAPE) ascii = 0x1b;
    else if (sym == SDLK_BACKSPACE) ascii = 0x08;
    else if (sym == SDLK_TAB) ascii = 0x09;
    else if (sym >= 32 && sym < 127) {
        ascii = (uint8_t)sym;
        if ((k->keysym.mod & KMOD_SHIFT) && ascii >= 'a' && ascii <= 'z')
            ascii = (uint8_t)(ascii - 32);
    }
    if (sc == 0 && ascii == 0) return 0;
    return (uint16_t)((sc << 8) | ascii);
}

void hw_key_event(const SDL_KeyboardEvent *k, int down)
{
    uint8_t sc = pc_scancode(k->keysym.scancode);
    if (atomic_load(&s_kbd_isr_on)) {
        if (sc) kbd_isr((uint8_t)(sc | (down ? 0 : 0x80)));
        return;
    }
    if (down) {
        uint16_t c = bios_code(k);
        if (c) bios_key_push(c);
    }
}

/* ------------------------------------------------------------------ */
/* vertical retrace                                                    */
/* ------------------------------------------------------------------ */
void hw_vsync_signal(void) { atomic_fetch_add(&s_vsync_count, 1); }

void hw_wait_vsync(void)
{
    unsigned start = atomic_load(&s_vsync_count);
    int guard = 0;
    while (atomic_load(&s_vsync_count) == start && guard++ < 40)
        SDL_Delay(1);
}

/* ------------------------------------------------------------------ */
void hw_start(void)
{
    SDL_CreateThread(timer_thread, "pit", NULL);
}

/* ------------------------------------------------------------------ */
/* mouse (INT 33h) and joystick (port 201h) emulation                  */
/* ------------------------------------------------------------------ */
static atomic_int s_mouse_x = 320, s_mouse_y = 100, s_mouse_btn;
static atomic_int s_joy_x, s_joy_y, s_joy_btn;   /* axis -32768..32767 */

void hw_mouse_motion(int dx, int dy)
{
    int x = atomic_load(&s_mouse_x) + dx, y = atomic_load(&s_mouse_y) + dy;
    if (x < 0) x = 0;
    if (x > 639) x = 639;
    if (y < 0) y = 0;
    if (y > 199) y = 199;
    atomic_store(&s_mouse_x, x);
    atomic_store(&s_mouse_y, y);
}
void hw_mouse_buttons(int b) { atomic_store(&s_mouse_btn, b); }
void hw_joystick(int x, int y, int buttons)
{
    atomic_store(&s_joy_x, x); atomic_store(&s_joy_y, y); atomic_store(&s_joy_btn, buttons);
}
int hw_mouse_mode(void) { return g_ds && DS16(0x95f6) == 2; }

/* 1000:068b  INT 33h AX=0,1,2: reset / show / hide */
void FUN_1000_068b(void) { atomic_store(&s_mouse_x, 320); atomic_store(&s_mouse_y, 100); }

/* 1000:06a4  INT 33h AX=4: set position */
void FUN_1000_06a4(int x, int y)
{
    atomic_store(&s_mouse_x, (uint16_t)x);
    atomic_store(&s_mouse_y, (uint16_t)y);
}

/* 1000:06b9  INT 33h AX=3: 0 = x, 1 = y, 2 = buttons */
int16_t FUN_1000_06b9(int what)
{
    switch ((int16_t)what) {
        case 0: return (int16_t)atomic_load(&s_mouse_x);
        case 1: return (int16_t)atomic_load(&s_mouse_y);
        case 2: return (int16_t)atomic_load(&s_mouse_btn);
        default: return 0;
    }
}

/* 1000:05f6  joystick axis timing (1 = x, 2 = y); centre ~1000 */
int16_t FUN_1000_05f6(int axis)
{
    int v = ((int16_t)axis == 1) ? atomic_load(&s_joy_x) : atomic_load(&s_joy_y);
    return (int16_t)(1000 + v * 1000 / 32768);
}

/* 1000:0672  joystick buttons (bit set = pressed) */
uint8_t FUN_1000_0672(void) { return (uint8_t)(atomic_load(&s_joy_btn) & 0xf); }

/* Feed a PC scancode (and optional BIOS code) as if typed on the keyboard */
void hw_scancode_event(uint8_t sc, uint16_t bios, int down)
{
    if (atomic_load(&s_kbd_isr_on)) {
        kbd_isr((uint8_t)(sc | (down ? 0 : 0x80)));
        return;
    }
    if (down && bios) bios_key_push(bios);
}
