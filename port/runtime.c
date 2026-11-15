/* Native implementations of the decompiled DOS/BIOS/compiler-runtime helpers.
 * See runtime.h and docs in transform.py. */
#include "compat.h"
#include "protos.h"
#include <unistd.h>
#include <strings.h>
#include <stdatomic.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
void SDL_Delay(uint32_t ms);
static void SDL_Delay_hint(void) { SDL_Delay(1); }


/* ------------------------------------------------------------------ */
/* globals                                                             */
/* ------------------------------------------------------------------ */
uint8_t *g_mem;
uint8_t *g_ds;
uint8_t  g_stack_dummy;
uint16_t g_dsp = 0xfff0;   /* DS stack pointer (see compat.h) */
uint8_t  g_framebuffer[320 * 200];
uint8_t  g_palette[256][3];

#define DS16(off) (*(uint16_t *)(g_ds + (off)))
#define DS8(off)  (*(uint8_t  *)(g_ds + (off)))
#define DOS_ERR DS16(0x41b6)

/* ------------------------------------------------------------------ */
/* memory allocator: 16-byte paragraph blocks inside g_mem             */
/* ------------------------------------------------------------------ */
#define HEAP_START 0x27000u      /* conventional memory after the data segment */
#define HEAP_END   0xA0000u
#define HEAP2_START 0xB0000u     /* above VGA memory (still segment-addressable) */
#define HEAP2_END   0xF0000u      /* F000 segment: BIOS area (font) */
#define MAX_BLOCKS 8192

typedef struct { uint32_t start, size; int used; } Blk;
static Blk g_blocks[MAX_BLOCKS];
static int g_nblocks;

static void heap_init(void)
{
    int i;
    g_nblocks = 2;
    g_blocks[0].start = HEAP_START;
    g_blocks[0].size  = HEAP_END - HEAP_START;
    g_blocks[0].used  = 0;
    g_blocks[1].start = HEAP2_START;
    g_blocks[1].size  = HEAP2_END - HEAP2_START;
    g_blocks[1].used  = 0;
    for (i = 2; i < MAX_BLOCKS; i++) g_blocks[i].used = -1;
}

void FUN_1000_6660(int _dest_off, int _dest_seg, int _size)
{
    uint16_t dest_off = (uint16_t)_dest_off;
    uint16_t dest_seg = (uint16_t)_dest_seg;
    uint16_t size = (uint16_t)_size;
    uint8_t  *base = g_mem + ((uint32_t)dest_seg << 4);
    uint32_t  di = dest_off;
    uint32_t  end = (uint32_t)dest_off + size;
    uint8_t   len_bits, off_bits, long_bits;
    uint32_t  long_add;
    int       i;

    if (getenv("SKY_DEBUG")) fprintf(stderr, "[lzs start ptr=%x end=%x bits=%d byte=%02x size=%u]\n", DS16(0x41c2), DS16(0x41c0), DS16(0x41ba), DS8(0x41bc), size);
    len_bits  = FUN_1000_640a();
    off_bits  = FUN_1000_640a();
    long_add  = 1u << (off_bits & 0x1F);
    long_bits = FUN_1000_640a();

    while (di < end) {
        uint32_t offset, len, count, si;
        if (FUN_1000_6425() == 0) {
            offset = 0;
            for (i = 0; i < off_bits; i++)
                offset = (offset << 1) | (uint32_t)FUN_1000_6425();
        } else if (FUN_1000_6425() == 0) {
            offset = 0;
            for (i = 0; i < long_bits; i++)
                offset = (offset << 1) | (uint32_t)FUN_1000_6425();
            offset += long_add;
        } else {
            uint8_t lit = 0;
            for (i = 0; i < 8; i++)
                lit = (uint8_t)((lit << 1) | FUN_1000_6425());
            if (di < end) base[di++] = lit;
            continue;
        }
        len = 0;
        for (i = 0; i < len_bits; i++)
            len = (len << 1) | (uint32_t)FUN_1000_6425();
        if (len + 1 >= end - di) break;
        si = di - 2 - offset;
        count = len + 2;
        while (count-- != 0 && di < end) base[di++] = base[si++];
    }
    if (getenv("SKY_DEBUG")) fprintf(stderr, "[lzs end di=%x end=%x ptr=%x]\n", di, end, DS16(0x41c2));
    /* The original falls through into DS:0000, which holds
     * "call 6679 / pop di / pop si / leave / ret": byte-align the stream. */
    FUN_1000_65f3();
}

static uint16_t heap_alloc(uint32_t size)
{
    int i;
    size = (size + 15u) & ~15u;
    if (size == 0) size = 16;
    for (i = 0; i < g_nblocks; i++) {
        if (g_blocks[i].used || g_blocks[i].size < size) continue;
        if (g_blocks[i].size == size) {
            g_blocks[i].used = 1;
        } else {
            if (g_nblocks >= MAX_BLOCKS) return 0xFFFF;
            /* insert a used block at the front of the free block */
            memmove(&g_blocks[i + 1], &g_blocks[i],
                    (g_nblocks - i) * sizeof(Blk));
            g_nblocks++;
            g_blocks[i].used  = 1;
            g_blocks[i].size  = size;
            g_blocks[i + 1].start += size;
            g_blocks[i + 1].size  -= size;
        }
        return (uint16_t)(g_blocks[i].start >> 4);
    }
    return 0xFFFF;
}

/* DOS 4Ah: resize a block in place */
static int heap_resize(uint16_t seg, uint32_t size)
{
    uint32_t start = (uint32_t)seg << 4;
    int i;
    size = (size + 15u) & ~15u;
    for (i = 0; i < g_nblocks; i++) {
        Blk *b = &g_blocks[i];
        if (b->used != 1 || b->start != start) continue;
        if (size <= b->size) {
            uint32_t rest = b->size - size;
            if (rest && g_nblocks < MAX_BLOCKS) {
                memmove(&g_blocks[i + 2], &g_blocks[i + 1], (g_nblocks - i - 1) * sizeof(Blk));
                g_nblocks++;
                b->size = size;
                g_blocks[i + 1].start = start + size;
                g_blocks[i + 1].size = rest;
                g_blocks[i + 1].used = 0;
                if (i + 2 < g_nblocks && !g_blocks[i + 2].used &&
                    g_blocks[i + 1].start + rest == g_blocks[i + 2].start) {
                    g_blocks[i + 1].size += g_blocks[i + 2].size;
                    memmove(&g_blocks[i + 2], &g_blocks[i + 3], (g_nblocks - i - 3) * sizeof(Blk));
                    g_nblocks--;
                }
            }
            return 1;
        }
        if (i + 1 < g_nblocks && !g_blocks[i + 1].used &&
            b->start + b->size == g_blocks[i + 1].start &&
            b->size + g_blocks[i + 1].size >= size) {
            uint32_t need = size - b->size;
            g_blocks[i + 1].start += need;
            g_blocks[i + 1].size -= need;
            b->size = size;
            if (g_blocks[i + 1].size == 0) {
                memmove(&g_blocks[i + 1], &g_blocks[i + 2], (g_nblocks - i - 2) * sizeof(Blk));
                g_nblocks--;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}

static void heap_free(uint16_t seg)
{
    uint32_t start = (uint32_t)seg << 4;
    int i;
    for (i = 0; i < g_nblocks; i++) {
        if (g_blocks[i].used == 1 && g_blocks[i].start == start) {
            g_blocks[i].used = 0;
            /* coalesce with following block */
            if (i + 1 < g_nblocks && !g_blocks[i + 1].used &&
                g_blocks[i].start + g_blocks[i].size == g_blocks[i + 1].start) {
                g_blocks[i].size += g_blocks[i + 1].size;
                memmove(&g_blocks[i + 1], &g_blocks[i + 2],
                        (g_nblocks - i - 2) * sizeof(Blk));
                g_nblocks--;
            }
            /* coalesce with previous block */
            if (i > 0 && !g_blocks[i - 1].used &&
                g_blocks[i - 1].start + g_blocks[i - 1].size == g_blocks[i].start) {
                g_blocks[i - 1].size += g_blocks[i].size;
                memmove(&g_blocks[i], &g_blocks[i + 1],
                        (g_nblocks - i - 1) * sizeof(Blk));
                g_nblocks--;
            }
            return;
        }
    }
}

/* ------------------------------------------------------------------ */
/* timer / PC speaker                                                  */
/* ------------------------------------------------------------------ */
#define PIT_HZ 1193182u

static uint64_t pit_epoch;      /* plat_millis() when we last latched 0    */
static uint16_t pit_counter;    /* latched counter value                   */
static uint16_t pit_latch[3];   /* last written reload values              */
static uint8_t  speaker_ctrl;

static uint16_t pit_read_counter(void)
{
    /* Approximate: the 8253 counts down at PIT_HZ. */
    uint64_t us = (plat_millis() - pit_epoch) * 1000u;
    uint32_t ticks = (uint32_t)((us * PIT_HZ) / 1000000u) + pit_counter;
    return (uint16_t)(0x10000u - (ticks & 0xFFFF));
}

static void pit_write(unsigned reg, uint16_t val)
{
    if (reg < 3) pit_latch[reg] = val;
}


/* ------------------------------------------------------------------ */
/* port I/O                                                            */
/* ------------------------------------------------------------------ */
uint16_t port_in(uint16_t port)
{
    switch (port) {
        case 0x40: case 0x41: case 0x42:
            return pit_read_counter() & 0xFF;
        case 0x43: return 0;
        case 0x61: return speaker_ctrl;
        case 0x201: return 0x20;              /* no joystick buttons */
        case 0x3c5: case 0x3c9: case 0x3ce:
            return vga_port_in(port);
        default: return 0;
    }
}

void port_out(uint16_t port, uint16_t val)
{
    switch (port) {
        case 0x40: case 0x41: case 0x42:
            pit_write(port - 0x40, val & 0xFF);
            if ((port - 0x40) == 0) { pit_epoch = plat_millis(); pit_counter = 0; }
            return;
        case 0x43: pit_write(3, val & 0xFF); return;
        case 0x61:
            speaker_ctrl = val & 0xFF;
            if ((val & 3) == 3) snd_speaker_on(pit_latch[2]);
            else snd_speaker_off();
            return;
        case 0x3c4: case 0x3c5: case 0x3c8: case 0x3c9:
        case 0x3ce: case 0x3cf:
            vga_port_out(port, val);
            return;
        default:
            return;
    }
}

/* ------------------------------------------------------------------ */
/* file handles                                                        */
/* ------------------------------------------------------------------ */
#define MAX_HANDLES 64
static SkyFile *g_handles[MAX_HANDLES];
static char g_handle_names[MAX_HANDLES][16];

static int handle_alloc(SkyFile *f)
{
    int i;
    for (i = 5; i < MAX_HANDLES; i++) {
        if (!g_handles[i]) {
            g_handles[i] = f;
            if (getenv("SKY_DEBUG")) fprintf(stderr, "[alloc handle %d]\n", i);
            return i;
        }
    }
    return -1;
}

static SkyFile *handle_get(uint16_t h)
{
    if (h < MAX_HANDLES && g_handles[h]) return g_handles[h];
    if (getenv("SKY_DEBUG")) fprintf(stderr, "[bad handle %u from %p]\n", h, __builtin_return_address(0));
    return NULL;
}

/* ------------------------------------------------------------------ */
/* Buffered bit reader (the original self-modifying LZS bit reader)    */
/* ------------------------------------------------------------------ */
#define RD_HANDLE  DS16(0x41b8)
#define RD_BITS    DS16(0x41ba)
#define RD_BYTE    DS8(0x41bc)
#define RD_START   DS16(0x41be)
#define RD_END     DS16(0x41c0)
#define RD_PTR     DS16(0x41c2)
#define RD_SUM     DS16(0x41c4)
#define RD_FLAG    DS8(0x41c8)
#define RD_BB      DS8(0x41c7)

#define RDBUF 0x31b4

/* ------------------------------------------------------------------ */
/* string / memory / math                                              */
/* ------------------------------------------------------------------ */
void FUN_1000_5cc8(uintptr_t dst, int _val, int _n)
{
    uint8_t val = (uint8_t)_val;
    int16_t n = (int16_t)_n;
    memset(near_ptr(dst), val, (uint16_t)n);
}
void FUN_1000_5ca4(uintptr_t dst, uintptr_t src, int _n)
{
    int16_t n = (int16_t)_n;
    memmove(near_ptr(dst), near_ptr(src), (uint16_t)n);
}
void FUN_1000_5cf4(uintptr_t dst, uintptr_t src)
{
    strcpy((char *)near_ptr(dst), (char *)near_ptr(src));
}
uintptr_t FUN_1000_5cdc(uintptr_t a, int ch)
{
    char *p = strchr((char *)near_ptr(a), ch & 0xff);
    if (!p) return 0;
    return (uintptr_t)(p - (char *)g_ds) < 0x10000 ? (uintptr_t)(p - (char *)g_ds) : (uintptr_t)p;
}
int32_t FUN_1000_5d0e(int _a, int _b, int _c, int _d)
{
    uint16_t a = (uint16_t)_a;
    int16_t b = (int16_t)_b;
    uint16_t c = (uint16_t)_c;
    int16_t d = (int16_t)_d;
    /* 1000:5d0e  32-bit multiply (low 32 bits) */
    uint32_t x = ((uint32_t)(uint16_t)b << 16) | a;
    uint32_t y = ((uint32_t)(uint16_t)d << 16) | c;
    return (int32_t)(x * y);
}
uint32_t FUN_1000_5d4e(int _alo, int _ahi, int _blo, int _bhi)
{
    uint16_t alo = (uint16_t)_alo;
    uint16_t ahi = (uint16_t)_ahi;
    uint16_t blo = (uint16_t)_blo;
    uint16_t bhi = (uint16_t)_bhi;
    uint32_t a = ((uint32_t)ahi << 16) | alo;
    uint32_t b = ((uint32_t)bhi << 16) | blo;
    return b ? a / b : 0;
}
uint32_t FUN_1000_5db0(int _alo, int _ahi, int _blo, int _bhi)
{
    uint16_t alo = (uint16_t)_alo;
    uint16_t ahi = (uint16_t)_ahi;
    uint16_t blo = (uint16_t)_blo;
    uint16_t bhi = (uint16_t)_bhi;
    uint32_t a = ((uint32_t)ahi << 16) | alo;
    uint32_t b = ((uint32_t)bhi << 16) | blo;
    return b ? a % b : 0;
}
uint16_t FUN_1000_5d42(void) { return 0; }

void FUN_1000_5f96(int _c)
{
    uint8_t c = (uint8_t)_c;
    putchar(c);
    fflush(stdout);
}

/* ------------------------------------------------------------------ */
/* DOS file wrappers                                                   */
/* ------------------------------------------------------------------ */
uint16_t FUN_1000_6202(int _lo, int _hi)
{
    uint16_t lo = (uint16_t)_lo;
    uint16_t hi = (uint16_t)_hi;
    uint32_t size = ((uint32_t)hi << 16) | lo;
    uint16_t seg = heap_alloc(size);
    if (seg == 0xFFFF) {
        DOS_ERR = 8;
        if (getenv("SKY_DEBUG")) {
            int i;
            fprintf(stderr, "[alloc of %u failed]\n", size);
            for (i = 0; i < g_nblocks; i++)
                fprintf(stderr, "  blk %05x %6u %s\n", g_blocks[i].start, g_blocks[i].size, g_blocks[i].used ? "used" : "free");
        }
    }
    return seg;
}

uint16_t FUN_1000_5bdc(void)
{
    return 0xFFFF;      /* generic helper without size: should not be used */
}
uint16_t FUN_1000_5bbf(void)
{
    return 0xFFFF;
}

void FUN_1000_6015(int _dst_off, int _dst_seg, int _src_off, int _src_seg, int _len)
{
    uint16_t dst_off = (uint16_t)_dst_off;
    uint16_t dst_seg = (uint16_t)_dst_seg;
    uint16_t src_off = (uint16_t)_src_off;
    uint16_t src_seg = (uint16_t)_src_seg;
    uint16_t len = (uint16_t)_len;
    memmove(g_mem + ((uint32_t)dst_seg << 4) + dst_off,
            g_mem + ((uint32_t)src_seg << 4) + src_off, len);
}

void FUN_1000_4469(int _param_1, uintptr_t p2)
{
    int16_t param_1 = (int16_t)_param_1;
    uint16_t *param_2 = (uint16_t *)near_ptr(p2);
    /* 1000:4469  copy palette {seg, first, count} into DS:param_1 */
    uint16_t dst_off = (uint16_t)param_1 + (uint16_t)(3 * param_2[1]);
    uint16_t len = (uint16_t)(3 * param_2[2]);
    FUN_1000_6015(dst_off, 0x166e, 0, param_2[0], len);
}

void FUN_1000_4b27(uintptr_t p1, int _param_2)
{
    uint16_t param_2 = (uint16_t)_param_2;
    uint16_t *param_1 = (uint16_t *)near_ptr(p1);
    uint16_t seg;
    seg = FUN_1000_3ed8(0x300, 0);
    param_1[0] = seg;
    FUN_1000_0069();
    FUN_1000_6015(0, seg, param_2, 0x166e, 0x300);
    param_1[1] = 0;
    param_1[2] = 0x100;
}

uint16_t FUN_1000_55f8(int _param_1)
{
    uint16_t param_1 = (uint16_t)_param_1;
    uint16_t handle, off, len;
    FUN_1000_5cc8(0x1638, 0, 7000);
    handle = FUN_1000_5c38(0xe14);
    FUN_1000_5c67(handle, (int16_t)(param_1 << 2), 0, 0);
    FUN_1000_5f3f(handle, (uintptr_t)&off, 2);
    FUN_1000_5f3f(handle, (uintptr_t)&len, 2);
    FUN_1000_5c67(handle, (int16_t)off, 0, 0);
    FUN_1000_639a(handle, 0, 0x1000, 0);
    DS16(0x456e) = FUN_1000_64f0();
    DS16(0x54ae) = FUN_1000_64f0();
    DS16(0x4574) = FUN_1000_64f0();
    FUN_1000_650f(0x41d0, 0x166e, 0xd8);
    FUN_1000_6660(0x1638, 0x166e, len);
    FUN_1000_5c1a(handle);
    return (uint16_t)((len / 7) / 2);
}

/* ------------------------------------------------------------------ */
/* The game's own sound setting (Controls screen: DS:451a, 0 = on),    */
/* also switched by the web page's settings menu.                      */
/* ------------------------------------------------------------------ */
static int s_want_song = -1;            /* last song the game asked for */
static atomic_int s_sound_req = -1;     /* from the page: 1 on, 0 off   */
static int s_in_controls;               /* the Controls screen is showing */

/* the menu screen last opened (its .lzs), for SKY_ROAD in platform.c */
static char s_screen[16];
static int s_screen_n;
const char *sky_screen(int *n) { if (n) *n = s_screen_n; return s_screen; }
static atomic_int s_cfg_reload;         /* the page changed the saved values */

/* Game thread, at frame and key-wait points: finish a change made from the
 * page the way the Controls screen (1000:4c04) does: restart the music when
 * sound comes back on (or silence it again if a song started meanwhile) and
 * save the setting. */
void sound_poll(void)
{
    int on, controls = s_in_controls;
    if (atomic_exchange(&s_cfg_reload, 0) && g_ds) {
        /* the account sync rewrote the saved settings / road completions:
         * read them again (1000:571b) and follow a sound change */
        int was_on = DS16(0x4528) == 0;
        FUN_1000_571b();
        s_in_controls = controls;           /* (reading it is not a screen) */
        if ((DS16(0x4528) == 0) != was_on) {
            if (DS16(0x4528) == 0) {
                DS16(0xbc2) = 0xffff;
                if (s_want_song >= 0) FUN_1000_57a8(s_want_song);
            } else {
                FUN_1000_5889();
                DS16(0xbc2) = 0xffff;
            }
        }
        if (controls) FUN_1000_4ae2();
    }
    on = atomic_exchange(&s_sound_req, -1);
    if (on < 0 || !g_ds) return;
#ifndef __EMSCRIPTEN__
    if (!on && DS16(0x4528) != 0) {     /* natively off stops the music */
        FUN_1000_5889();
        DS16(0xbc2) = 0xffff;
    }
#endif
    /* off from the page only mutes: the song plays on unheard (the page
     * stops the audio output) and continues when sound comes back on; a
     * song asked for meanwhile is not started (FUN_1000_57a8), so start it */
    if (on && DS16(0x4528) == 0 && DS16(0xbc2) == 0xffff && s_want_song >= 0)
        FUN_1000_57a8(s_want_song);
    FUN_1000_5770();                    /* skyroads.cfg */
    s_in_controls = controls;           /* (saving it marks leaving Controls) */
    if (controls) FUN_1000_4ae2();      /* Controls screen: move the marks */
}

#ifndef __EMSCRIPTEN__
#define EMSCRIPTEN_KEEPALIVE
#endif
EMSCRIPTEN_KEEPALIVE int sky_sound_on(void) { return g_ds && DS16(0x4528) == 0; }

#ifdef __EMSCRIPTEN__
/* main thread: skyroads.cfg's values (localStorage) changed, re-read them */
EMSCRIPTEN_KEEPALIVE void sky_reload_cfg(void) { atomic_store(&s_cfg_reload, 1); }
#endif

/* main thread (settings menu, the S key): switch the setting at once (new
 * songs and effects follow it), the rest in sound_poll.  On the web the
 * music is not stopped: the page mutes the output (sky_audio_mute) so the
 * song carries on; natively sound_poll stops it. */
EMSCRIPTEN_KEEPALIVE void sky_set_sound(int on)
{
    if (!g_ds || (DS16(0x4528) == 0) == (on != 0)) return;
    DS16(0x4528) = on ? 0 : 1;
    atomic_store(&s_sound_req, on != 0);
}

void FUN_1000_57a8(int _param_1)
{
    uint16_t param_1 = (uint16_t)_param_1;
    uint16_t h, off, mid, size;
    s_want_song = param_1;              /* to resume when sound comes back on */
    if (DS16(0xbc2) == param_1) return;
    FUN_1000_5889();
    if (DS16(0x4528) != 0) { DS16(0xbc2) = 0xffff; return; }   /* none playing */
    h = FUN_1000_5c38(0xe1e);
    DS16(0x41b8) = h;
    {
        uint8_t entry[6];
        FUN_1000_5c67(h, (int16_t)(param_1 * 6), 0, 0);
        FUN_1000_5f3f(h, (uintptr_t)entry, 6);
        off  = entry[0] | (entry[1] << 8);
        mid  = entry[2] | (entry[3] << 8);
        size = entry[4] | (entry[5] << 8);
    }
    FUN_1000_5c67(h, (int16_t)off, 0, 0);
    FUN_1000_639a(h, 0, 0x1000, 0);
    if (size < 0x3e80) FUN_1000_6660(0x54bc, 0x166e, size);
    else FUN_1000_5c0a(0xff);
    FUN_1000_4120();
    if (DS16(0x41b6) == 0) {
        FUN_1000_5a61((uint16_t)(mid * 0x10 + 0x54bc), 0x54bc);
        DS16(0xbc2) = param_1;
    }
}

void FUN_1000_00bb(void)
{
    uint16_t handle = FUN_1000_5c38(0xd08);
    int index = 0;
    FUN_1000_639a(handle, 0, 0x1000, 0);
    while (DOS_ERR == 0) {
        uint16_t size, csize, seg;
        size  = FUN_1000_64f0();
        csize = FUN_1000_64f0();
        if (DOS_ERR) break;
        if (DS16(0x456c) == 0) {
            uint16_t s = FUN_1000_3ed8(0x7d64, 0);
            DS16(0x456c) = s;
            if ((uint16_t)((s + 0x7d7) & 0xf000) != (uint16_t)(s & 0xf000)) {
                FUN_1000_3f56();        /* crosses a DMA page: not usable */
                DS16(0x456c) = 0;
            }
        }
        seg = FUN_1000_3ed8(size, 0);
        DS16(0xe82 + index * 2) = seg;
        *(uint16_t *)(g_mem + ((uint32_t)seg << 4)) =
            (uint16_t)(size - csize);
        FUN_1000_6660((uint16_t)(size - csize), seg, csize);
        index++;
        if (index > 40) break;
    }
    FUN_1000_5bf5();
    FUN_1000_5c1a(handle);
}

/* 1000:03c2  start sound effect `idx` (PC speaker sequence or SB sample) */
void speaker_gate(int on);
void sb_play(const uint8_t *data, uint16_t len, uint8_t time_const);
void FUN_1000_03c2(int _idx)
{
    int16_t idx = (int16_t)_idx;
    DS16(0xaf48) = DS16(0x160c);
    if (DS16(0x4528) != 0) return;          /* sound off */
    if (DS16(0xcc2) == 0) {
        speaker_gate(1);
        DS16(0xba0) = DS16(0x132 + idx * 2);
    } else {
        uint8_t *snd = g_mem + ((uint32_t)DS16(0x456c) << 4);
        uint16_t a = *(uint16_t *)(snd + idx * 2);
        uint16_t b = *(uint16_t *)(snd + (idx + 1) * 2);
        sb_play(snd + a + 1, (uint16_t)(b - a - 1), snd[a]);
    }
}

void FUN_1000_6061(int _seg)
{
    uint16_t seg = (uint16_t)_seg;
    heap_free(seg);
}

uint16_t FUN_1000_5c38(uintptr_t name)
{
    SkyFile *f;
    int h;
    {   /* the Controls screen (1000:4c04) opens setmenu.lzs and saves
         * skyroads.cfg when it is left; any other file but the music also
         * means another screen (see sound_poll) */
        const char *n = (const char *)near_ptr(name);
        if (strcasecmp(n, "gomenu.lzs") == 0 || strcasecmp(n, "mainmenu.lzs") == 0) {
            snprintf(s_screen, sizeof s_screen, "%s", n);
            s_screen_n++;
        }
        if (strcasecmp(n, "setmenu.lzs") == 0) s_in_controls = 1;
        else if (strcasecmp(n, "muzax.lzs") != 0) s_in_controls = 0;
        plat_file_opened(n);            /* widescreen: which road backdrop */
    }
    if (DOS_ERR) return 0xFFFF;
    f = sky_open((const char *)near_ptr(name));
    if (!f) { DOS_ERR = 2; return 0xFFFF; }
    h = handle_alloc(f);
    if (h < 0) { sky_close(f); DOS_ERR = 4; return 0xFFFF; }
    snprintf(g_handle_names[h], 16, "%s", (const char *)near_ptr(name));
    return (uint16_t)h;
}

uint16_t FUN_1000_5c2b(uintptr_t name, int mode)
{
    SkyFile *f;
    int h;
    if (strcasecmp((const char *)near_ptr(name), "skyroads.cfg") == 0)
        s_in_controls = 0;              /* 1000:4c04 saves when it returns */
    if (DOS_ERR) return 0xFFFF;
    f = sky_create((const char *)near_ptr(name));
    if (!f) { DOS_ERR = 3; return 0xFFFF; }
    h = handle_alloc(f);
    if (h < 0) { sky_close(f); DOS_ERR = 4; return 0xFFFF; }
    return (uint16_t)h;
}

void FUN_1000_5c1a(int _handle)
{
    uint16_t handle = (uint16_t)_handle;
    SkyFile *f = handle_get(handle);
    if (f) { sky_close(f); g_handles[handle] = NULL; }
}

int16_t FUN_1000_5c67(int _handle, int _lo, int _hi, int _whence)
{
    uint16_t handle = (uint16_t)_handle;
    int16_t lo = (int16_t)_lo;
    int16_t hi = (int16_t)_hi;
    int16_t whence = (int16_t)_whence;
    SkyFile *f = handle_get(handle);
    long off = (long)(int32_t)(((uint32_t)(uint16_t)hi << 16) | (uint16_t)lo);
    long pos;
    if (DOS_ERR) return -1;
    if (!f) { DOS_ERR = 6; return -1; }
    pos = sky_seek(f, off, whence);
    if (pos < 0) { DOS_ERR = 0x19; return -1; }
    return (int16_t)pos;
}

/* how bright the screen's palette is, 0-100: 1000:4b72 fades between the
 * palette and black through 1000:4315; the widescreen margins' true-colour
 * pictures follow it (platform.c) */
static atomic_int s_fade = 100;
int sky_fade_level(void) { return atomic_load(&s_fade); }

static int palette_black(const uint16_t *pal)
{
    const uint8_t *p = g_mem + ((uint32_t)pal[0] << 4);
    int i, n = (int16_t)pal[2] * 3;
    for (i = 0; i < n; i++) if (p[i]) return 0;
    return 1;
}

void FUN_1000_4315(uintptr_t p1, uintptr_t p2, int _param_3)
{
    uint16_t param_3 = (uint16_t)_param_3;
    uint16_t *param_1 = (uint16_t *)near_ptr(p1);
    uint16_t *param_2 = (uint16_t *)near_ptr(p2);
    if (DS16(0x36) != 0) {
        int local_6;
        int from_black = palette_black(param_1), to_black = palette_black(param_2);
        DS16(0x160c) = 0;
        do {
            int i, n;
            uint8_t *src, *dst, *out;
            if (param_3 == 0) local_6 = 100;
            else local_6 = (int)(((int32_t)DS16(0x160c) * 100) / param_3);
            if (local_6 > 100 || DS16(0x54ac) != 0) local_6 = 100;
            if (from_black && !to_black) atomic_store(&s_fade, local_6);
            else if (to_black && !from_black) atomic_store(&s_fade, 100 - local_6);
            src = g_mem + ((uint32_t)param_1[0] << 4);
            dst = g_mem + ((uint32_t)param_2[0] << 4);
            out = g_ds + 0x31b4;
            n = (int16_t)param_1[2] * 3;
            for (i = 0; i < n; i++) {
                *out = (uint8_t)(*src + (int8_t)((int16_t)(((uint16_t)*dst - (uint16_t)*src) * local_6) / 100));
                out++; src++; dst++;
            }
            FUN_1000_6233(param_1[1], param_1[2], 0x31b4, 0x166e);
            FUN_1000_4137();
        } while (local_6 != 100);
    }
}

void FUN_1000_5f3f(int _handle, uintptr_t buf, int _len)
{
    uint16_t handle = (uint16_t)_handle;
    int16_t len = (int16_t)_len;
    SkyFile *f;
    int n;
    if (DOS_ERR) return;
    f = handle_get(handle);
    if (!f) { DOS_ERR = 6; return; }
    n = sky_read(f, near_ptr(buf), (uint16_t)len);
    if (n != (int)(uint16_t)len) {
        if (getenv("SKY_DEBUG")) fprintf(stderr, "[short read %d/%d h=%d]\n", n, (int)(uint16_t)len, handle);
        DOS_ERR = 0x14;
    }
}

int16_t FUN_1000_606d(int _handle, uintptr_t buf, int _len)
{
    uint16_t handle = (uint16_t)_handle;
    int16_t len = (int16_t)_len;
    SkyFile *f = handle_get(handle);
    int n;
    if (!f) { DOS_ERR = 6; return -1; }
    n = sky_write(f, near_ptr(buf), (uint16_t)len);
    if (n != (int)(uint16_t)len) DOS_ERR = 0x13;
    return (int16_t)n;
}

/* 1000:5fc3  DOS 4Ch: terminate */
void game_exit(int code);
void FUN_1000_5fc3(int code) { game_exit(code); }

/* ------------------------------------------------------------------ */
/* BIOS / video mode                                                   */
/* ------------------------------------------------------------------ */
void FUN_1000_5fdf(int _mode)
{
    uint16_t mode = (uint16_t)_mode;
    extern void video_set_mode(int mode);
    video_set_mode(mode);
    DS16(0x36) = 1;      /* pretend we are a VGA (mode 13h path) */
}

uint16_t FUN_1000_5fe9(void) { return 1; }   /* EGA/VGA present */
uint16_t FUN_1000_5ffd(void) { return 1; }   /* VGA present      */

void FUN_1000_0e23(void)
{
    if (DS16(0x36) == 0) video_set_mode(0x0d);
}

#include "font8x8.h"
void FUN_1000_0000(void)
{
    /* INT 10h AX=1130h: 8x8 font pointers (BH=3: chars 0-127, BH=4: 128-255).
     * The font lives at FE00:0000 in the emulated address space. */
    memcpy(g_mem + 0xFE000, vga_font8x8, sizeof(vga_font8x8));
    DS16(0x3194) = 0x0000; DS16(0x3196) = 0xFE00;
    DS16(0x3198) = 0x0400; DS16(0x319a) = 0xFE00;
    if (DS16(0x36) == 0) video_set_mode(0x0d);
    else                 video_set_mode(0x13);
    /* The original also stores the BIOS font pointer; not needed here. */
}

void FUN_1000_60c1(uint16_t a) { (void)a; }   /* set palette via BIOS */
uint8_t FUN_1000_6151(void) { return 0; }     /* sequencer clocking   */

/* 1000:6233  set `count` DAC registers from far pointer seg:off */
uint32_t FUN_1000_6233(int first, int count, int off, int seg)
{
    const uint8_t *p = g_mem + ((uint32_t)(uint16_t)seg << 4) + (uint16_t)off;
    plat_set_palette(first & 0xff, count & 0x1ff, p);
    return 0;
}

/* ------------------------------------------------------------------ */
/* buffered reader                                                     */
/* ------------------------------------------------------------------ */
void FUN_1000_636a(int _off, int _size)
{
    uint16_t off = (uint16_t)_off;
    uint16_t size = (uint16_t)_size;
    uint16_t base = RDBUF + off;
    uint16_t limit = 0x1000u - off;
    if (size < limit) limit = size;
    RD_START = base;
    RD_PTR   = base;
    RD_END   = base + limit;
    RD_SUM   = 0;
}

void FUN_1000_62de(void)
{
    int n;
    uint16_t len = RD_END - RD_START;
    SkyFile *f = handle_get(RD_HANDLE);
    RD_PTR = RD_START;
    if (!f) { RD_END = RD_START; RD_BYTE = 0; RD_BITS = 8; DOS_ERR = 6; return; }
    n = sky_read(f, g_ds + RD_START, len);
    if (n < 0) n = 0;
    if (n == 0) { n = 1; RD_BB = 1; }
    RD_END = RD_START + (uint16_t)n;
    FUN_1000_5bf5();
    RD_BYTE = *(g_ds + RD_PTR);
    RD_PTR++;
    RD_BITS = 8;
}

void FUN_1000_62ca(void)
{
    if (RD_BB) { if (getenv("SKY_DEBUG")) fprintf(stderr, "[read past EOF in %s]\n", RD_HANDLE < MAX_HANDLES ? g_handle_names[RD_HANDLE] : "?"); DOS_ERR = 0x14; return; }
    RD_SUM = 0;
    FUN_1000_62de();
}

void FUN_1000_62a0(void)
{
    if (RD_PTR == RD_END) { FUN_1000_62ca(); return; }
    RD_BYTE = *(g_ds + RD_PTR);
    RD_PTR++;
}

void FUN_1000_639a(int _handle, int _off, int _size, int _flag)
{
    uint16_t handle = (uint16_t)_handle;
    int16_t off = (int16_t)_off;
    int16_t size = (int16_t)_size;
    int16_t flag = (int16_t)_flag;
    RD_HANDLE = handle;
    RD_FLAG   = (uint8_t)flag;
    RD_BB     = 0;
    FUN_1000_636a(off, size);
    FUN_1000_62de();
    DS8(0x41c6) = 0;
}

void FUN_1000_63c4(int _handle, int _off, int _size, int _flag)
{
    uint16_t handle = (uint16_t)_handle;
    int16_t off = (int16_t)_off;
    int16_t size = (int16_t)_size;
    int16_t flag = (int16_t)_flag;
    RD_HANDLE = handle;
    RD_FLAG   = (uint8_t)flag;
    FUN_1000_636a(off, size);
    DS16(0x41ba) = 8;
    DS8(0x41c6) = 1;
}

uint8_t FUN_1000_640a(void)
{
    uint8_t b = RD_BYTE;
    FUN_1000_62a0();
    return b;
}

void FUN_1000_6413(int _b)
{
    uint8_t b = (uint8_t)_b;
    *(g_ds + RD_PTR) = b;
    RD_PTR++;
}

int16_t FUN_1000_6425(void)
{
    int bit = (RD_BYTE >> 7) & 1;
    RD_BYTE <<= 1;
    if (--RD_BITS == 0) {
        RD_BITS = 8;
        if (RD_PTR == RD_END) FUN_1000_62ca();
        else { RD_BYTE = *(g_ds + RD_PTR); RD_PTR++; }
    }
    return bit;
}

void FUN_1000_6479(int _n)
{
    uint16_t n = (uint16_t)_n;
    /* Not used directly in the ported decoder, but keep it for completeness. */
    (void)n;
}

void FUN_1000_65f3(void)
{
    /* discard the remaining bits of the current byte */
    if (RD_BITS != 8) {
        int n = RD_BITS;
        while (n-- > 0) FUN_1000_6425();
    }
}

uint16_t FUN_1000_64f0(void)
{
    uint8_t lo = FUN_1000_640a();
    uint8_t hi = FUN_1000_640a();
    return (uint16_t)((hi << 8) | lo);
}

void FUN_1000_650f(int _offset, int _segment, int _size)
{
    uint16_t offset = (uint16_t)_offset;
    uint16_t segment = (uint16_t)_segment;
    uint16_t size = (uint16_t)_size;
    /* Reads `size` raw bytes from the bit stream into segment:offset. */
    uint8_t *p = g_mem + ((uint32_t)segment << 4) + offset;
    while (size-- > 0) *p++ = FUN_1000_640a();
}

uint16_t FUN_1000_3f75(int _param_1, int _param_2)
{
    uint16_t param_1 = (uint16_t)_param_1;
    uint16_t param_2 = (uint16_t)_param_2;
    uint16_t n;
    FUN_1000_64f0();
    FUN_1000_64f0();
    n = FUN_1000_640a();
    if (DOS_ERR == 0)
        FUN_1000_650f((uint16_t)(param_1 + param_2 * 3), 0x166e, (uint16_t)(n * 3));
    FUN_1000_650f(0xaf4c, 0x166e, (uint16_t)(n * 2));
    return n;
}

uint16_t FUN_1000_3fc6(uintptr_t p1, int _param_2)
{
    uint16_t param_2 = (uint16_t)_param_2;
    uint16_t *param_1 = (uint16_t *)near_ptr(p1);
    uint16_t seg;
    FUN_1000_64f0();
    FUN_1000_64f0();
    param_1[1] = param_2;
    param_1[2] = FUN_1000_640a();
    seg = FUN_1000_3ed8((uint16_t)(param_1[2] * 3), 0);
    param_1[0] = seg;
    if (DOS_ERR == 0) {
        FUN_1000_650f(0, seg, (uint16_t)(param_1[2] * 3));
        FUN_1000_650f(0xaf4c, 0x166e, (uint16_t)(param_1[2] * 2));
    }
    return param_1[2];
}

void FUN_1000_4068(uintptr_t p1, int _param_2)
{
    uint16_t param_2 = (uint16_t)_param_2;
    uint16_t *param_1 = (uint16_t *)near_ptr(p1);
    uint16_t seg, iVar1;
    FUN_1000_64f0();
    { uint8_t *q = (uint8_t *)param_1; int k; for (k = 0; k < 8; k++) q[k] = FUN_1000_640a(); }
    iVar1 = (uint16_t)(param_1[2] * param_1[3]);
    seg = FUN_1000_3ed8(iVar1, 0);
    if (getenv("SKY_DEBUG")) fprintf(stderr, "[img pos=%u rows=%u w=%u seg=%04x err=%u]\n", param_1[1], param_1[2], param_1[3], seg, DOS_ERR);
    param_1[0] = seg;
    FUN_1000_0069();
    FUN_1000_6660(0, seg, iVar1);
    if (getenv("SKY_DUMP") && param_1[3] == 320) {
        char path[64]; FILE *fp;
        snprintf(path, sizeof path, "/tmp/img_%04x_%u.gray", seg, param_1[2]);
        fp = fopen(path, "wb");
        if (fp) { fwrite(g_mem + ((uint32_t)seg << 4), 1, iVar1, fp); fclose(fp); }
    }
    if (DS16(0x36) == 0) {
        FUN_1000_3d82(seg, param_1[2], param_1[3],
                      (param_1[1] & 1) ^ ((uint16_t)param_1[1] / 0x140 & 1));
    } else {
        FUN_1000_4036(0, seg, iVar1, 0, param_2);
    }
}

void FUN_1000_655a(int _a, int _b, int _n)
{
    uint16_t a = (uint16_t)_a;
    uint16_t b = (uint16_t)_b;
    uint16_t n = (uint16_t)_n;
    (void)a; (void)b; (void)n;
}

void FUN_1000_6599(uintptr_t dst, int _n)
{
    int16_t n = (int16_t)_n;
    uint8_t *p = (uint8_t *)near_ptr(dst);
    for (; n != 0; n--) {
        int c = FUN_1000_640a();
        *p++ = (uint8_t)c;
        if (c == 0) break;
    }
    for (; n != 0; n--) *p++ = 0x20;
}

void FUN_1000_65bf(uintptr_t a, int16_t n) { (void)a; (void)n; }
uint32_t FUN_1000_6616(uint8_t *p, int _n, uint32_t sum)
{
    int16_t n = (int16_t)_n;
    while (n--) sum = ((sum << 8) | (uint8_t)(sum + *p++));
    return sum;
}
void FUN_1000_631d(void) {}
void FUN_1000_6339(void) {}
void FUN_1000_634d(void) {}

/* ------------------------------------------------------------------ */
/* LZS / bit-stream decompressor                                       */
/* ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ */
/* sound (stubbed for now)                                             */
/* ------------------------------------------------------------------ */


/* ------------------------------------------------------------------ */
/* input                                                              */
/* ------------------------------------------------------------------ */

int kb_key_available(void);

/* 1000:5f8e  DOS 0Bh: key available? */
uint16_t FUN_1000_5f8e(void)
{
    if (kb_key_available()) return 1;
    SDL_Delay_hint();
    return 0;
}

/* 1000:5fad  DOS 07h: read key; extended keys return scan<<8 */
uint16_t FUN_1000_5fad(void)
{
    int c, waited = 0;
    static const char *autok;
    while ((c = kb_read_key()) < 0) {
        sound_poll();
        SDL_Delay_hint();
        /* test hook: SKY_AUTOKEYS="0d,0d,4800" feeds keys to blocking reads */
        if (++waited > 1000 && (autok || (autok = getenv("SKY_AUTOKEYS"))) && *autok) {
            char *end;
            c = (int)strtol(autok, &end, 16);
            autok = (*end == ',') ? end + 1 : end;
            if (getenv("SKY_DEBUG")) fprintf(stderr, "[autokey %04x]\n", c);
            if (c < 0x100) c |= 0x100;      /* fake scan code so ASCII path is used */
            break;
        }
    }
    if ((c & 0xff) == 0 || (c & 0xff) == 0xe0) return (uint16_t)(c & 0xff00);
    return (uint16_t)(c & 0xff);
}

/* ------------------------------------------------------------------ */
/* number formatting                                                   */
/* ------------------------------------------------------------------ */
void FUN_1000_5f14(uintptr_t ptr, int _value)
{
    uint16_t value = (uint16_t)_value;
    char buf[8];
    int i = 5;
    buf[i] = '\0';
    do { buf[--i] = (char)('0' + value % 10); value /= 10; } while (value);
    FUN_1000_5cf4((uintptr_t)ptr, (uintptr_t)buf + i);
}
void FUN_1000_5ece(uintptr_t ptr, int _lo, int _hi)
{
    uint16_t lo = (uint16_t)_lo;
    uint16_t hi = (uint16_t)_hi;
    uint32_t v = ((uint32_t)hi << 16) | lo;
    char buf[16];
    int i = 10;
    buf[i] = '\0';
    do { buf[--i] = (char)('0' + v % 10); v /= 10; } while (v);
    FUN_1000_5cf4((uintptr_t)ptr, (uintptr_t)buf + i);
}
void FUN_1000_5f77(int _handle, int _off, int _seg, int _len)
{
    uint16_t handle = (uint16_t)_handle;
    uint16_t off = (uint16_t)_off;
    uint16_t seg = (uint16_t)_seg;
    uint16_t len = (uint16_t)_len;
    SkyFile *f = handle_get(handle);
    int n;
    if (DOS_ERR) return;
    if (!f) { DOS_ERR = 6; return; }
    n = sky_read(f, g_mem + ((uint32_t)seg << 4) + off, len);
    if (n != (int)len) {
        if (getenv("SKY_DEBUG")) fprintf(stderr, "[short far read %d/%d h=%d]\n", n, (int)len, handle);
        DOS_ERR = 0x14;
    }
}
void FUN_1000_61ec(int _a, int _b)
{
    uint16_t a = (uint16_t)_a;
    uint16_t b = (uint16_t)_b;
    char buf[16];
    FUN_1000_5ece((uintptr_t)buf, a, b);
    FUN_1000_5c43((uintptr_t)buf);
}
void FUN_1000_5c43(uintptr_t str)
{
    char *p = (char *)near_ptr(str);
    while (*p) FUN_1000_5f96((uint8_t)*p++);
}

/* ------------------------------------------------------------------ */
/* entry point                                                         */
/* ------------------------------------------------------------------ */

void entry(void)
{
    heap_init();
    /* Force the VGA (mode 13h) code paths, as on any modern machine. */
    DS16(0x36) = 1;
    FUN_1000_01b8();
}

/* 1000:5c92  far memset(off:seg, val, n) */
void FUN_1000_5c92(int off, int seg, int val, int n)
{
    memset(g_mem + ((uint32_t)(uint16_t)seg << 4) + (uint16_t)off, val & 0xff, (uint16_t)n);
}

/* 1000:60ab  fatal error exit */
void FUN_1000_60ab(void) { FUN_1000_5fc3(1); }

/* 1000:5e1c  signed 32-bit division */
int32_t FUN_1000_5e1c(int alo, int ahi, int blo, int bhi)
{
    int32_t a = (int32_t)(((uint32_t)(uint16_t)ahi << 16) | (uint16_t)alo);
    int32_t b = (int32_t)(((uint32_t)(uint16_t)bhi << 16) | (uint16_t)blo);
    return b ? a / b : 0;
}

/* 1000:5eb8  strcat */
void FUN_1000_5eb8(uintptr_t dst, uintptr_t src)
{
    strcat((char *)near_ptr(dst), (const char *)near_ptr(src));
}

/* 1000:5c57  DOS 4Ah: resize memory block seg to `paras` paragraphs */
void FUN_1000_5c57(int seg, int paras)
{
    if (DOS_ERR) return;
    if (!heap_resize((uint16_t)seg, (uint32_t)(uint16_t)paras << 4)) DOS_ERR = 8;
}
