/* Compatibility layer for the decompiled SkyRoads (16-bit DOS) source.
 *
 * The original program is a small/medium model DOS executable.  It has a
 * 64 KiB data segment (DS), a separate 64 KiB code segment (CS), and uses
 * DOS far pointers for dynamically allocated buffers.  This header provides:
 *
 *   - the Ghidra pseudo types
 *   - a flat 1 MiB + real-mode address space (g_mem) so far pointers work
 *   - DS/CS base helpers
 *   - the PC hardware ports (PIT, VGA, speaker) and BIOS/DOS interrupt layer
 *
 * Near pointers in the decompiled source are turned into real C pointers
 * into g_ds by transform.py; literal DS offsets are wrapped with DS_ADDR().
 */
#ifndef SKYROADS_COMPAT_H
#define SKYROADS_COMPAT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Ghidra pseudo types ------------------------------------------------ */
typedef uint8_t  undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;

/* Flat real-mode address space.  We keep it a bit larger than 1 MiB so the
 * segment wrap tricks used by the original never go out of bounds. */
#define MEM_SIZE 0x120000
extern uint8_t *g_mem;

#define DS_BASE  0x16760u    /* 0x1000:0x6760  (CS base 0x1000) */
#define CS_BASE  0x10000u
#define VGA_BASE 0xA0000u
#define VGA_SEG  0xA000u

#define DS_ADDR(off) ((uint8_t *)(g_mem + DS_BASE + (uint32_t)(off)))
#define CS_ADDR(off) ((uint8_t *)(g_mem + CS_BASE + (uint32_t)(off)))
#define MEM_ADDR(a)  ((uint8_t *)(g_mem + (uint32_t)(a)))

/* The program's data segment, as a pointer. */
extern uint8_t *g_ds;

/* Compatibility with the Ghidra macros used by the generated code. */
#define CONCAT11(hi,lo) ((uint16_t)(((uint16_t)(uint8_t)(hi) << 8) | (uint8_t)(lo)))
#define CONCAT22(hi,lo) ((uint32_t)(((uint32_t)(uint16_t)(hi) << 16) | (uint16_t)(lo)))
#define CARRY1(a,b)     ((uint8_t)((((uint16_t)(a) + (uint16_t)(b)) >> 8) & 1))
#define CARRY2(a,b)     ((uint8_t)((((uint32_t)(a) + (uint32_t)(b)) >> 16) & 1))

/* Function calling convention decorations from the decompiler. */
#define __cdecl16near
#define __cdecl16far

/* Dummy location used for the decompiler's synthetic "&stack0xfffe" values. */
extern uint8_t g_stack_dummy;
#define stack0xfffe g_stack_dummy

/* Incoming register "undefined" values the decompiler left behind.  In the
 * original these were the caller's registers; the ported code paths that use
 * them are re-implemented by hand in runtime.c, but keep the names available
 * so the transformed code still compiles. */
#define unaff_DS 0x1676u
#define unaff_ES 0x1676u
#define unaff_SS 0x218au

/* PC port I/O.  Width is chosen by port; both return/accept the 16-bit AX. */
uint16_t port_in(uint16_t port);
void     port_out(uint16_t port, uint16_t val);

/* The decompiler mixes near pointers to the data segment (small 16-bit
 * offsets) with real native pointers.  near_ptr() resolves both: values
 * below 64 KiB are treated as DS offsets, anything else is already a native
 * pointer (e.g. &stack_local or a pointer into g_mem). */
static inline uint8_t *near_ptr(uintptr_t p) {
    /* user-space pointers on 64-bit macOS are always >= 4 GiB (on wasm32 the
     * build keeps them >= 64 KiB); small values
     * (possibly sign-extended) are 16-bit DS offsets.  The data segment is
     * 64 KiB aligned in host memory, so a truncated pointer into DS equals
     * its DS offset. */
#if UINTPTR_MAX > 0xffffffffu
    if (p < 0x100000000ull || p >= 0xffffffffffff0000ull)
        return g_ds + (uint16_t)p;
#else
    /* wasm32: the build places all host data above 64 KiB (see web/Makefile) */
    if (p < 0x10000u || p >= 0xffff0000u)
        return g_ds + (uint16_t)p;
#endif
    return (uint8_t *)p;
}

/* Stack frames of the generated functions live in the data segment, like the
 * original (SS == DS), so near pointers to locals are valid DS offsets. */
extern uint16_t g_dsp;
static inline uint8_t *ds_frame_alloc(unsigned size, uint16_t *saved) {
    *saved = g_dsp;
    g_dsp = (uint16_t)((g_dsp - size) & ~7u);
    if (g_dsp < 0xb140u) { fprintf(stderr, "DS stack overflow\n"); abort(); }
    memset(g_ds + g_dsp, 0, size);
    return g_ds + g_dsp;
}
static inline void ds_frame_release(uint16_t *saved) { g_dsp = *saved; }

/* Emulated BIOS/DOS timer. */
uint32_t timer_ticks(void);

/* ------------------------------------------------------------------ */
/* Native platform API (implemented in platform.c)                     */
/* ------------------------------------------------------------------ */
int  plat_init(void);
void plat_shutdown(void);
int  plat_pump_events(void);

/* 320x200 8-bit framebuffer that gets presented to the window. */
extern uint8_t g_framebuffer[320 * 200];
extern uint8_t g_palette[256][3];

void plat_present(void);
/* ghost.c */
void ghost_run_begin(void);
void ghost_run_end(void);
void ghost_frame(int16_t spr);
void ghost_publish(const uint8_t *depth);
#define DEPTH_NONE  255
#define DEPTH_FLOOR 254
#define DEPTH_MAX   253
void ghost_overlay(uint32_t *pixels, int pitch);
void plat_frame(void);
void plat_set_palette(int first, int count, const uint8_t *rgb);

/* Keyboard: returns a BIOS-style scan code / ASCII as the game expects. */
int  kb_read_key(void);      /* -1 if no key pending        */
void kb_clear(void);

/* High resolution wall clock in milliseconds. */
uint64_t plat_millis(void);

/* File helpers (implemented in platform.c over stdio). */
typedef struct SkyFile SkyFile;
SkyFile *sky_open(const char *name);
SkyFile *sky_create(const char *name);
int      sky_read(SkyFile *f, void *dst, int len);
int      sky_write(SkyFile *f, const void *src, int len);
long     sky_seek(SkyFile *f, long off, int whence);
long     sky_tell(SkyFile *f);
void     sky_close(SkyFile *f);
int      sky_eof(SkyFile *f);

/* VGA compatibility layer (video.c). */
void     video_set_mode(int mode);
uint16_t vga_port_in(uint16_t port);
void     vga_port_out(uint16_t port, uint16_t val);
void     video_blit(void);

/* Audio: 8-bit unsigned mono output queue (PC speaker / DAC emulation). */
void snd_init(void);
void snd_pause(void);
void snd_write_dac(uint8_t sample);
void snd_speaker_on(uint16_t divisor);
void snd_speaker_off(void);

#endif /* SKYROADS_COMPAT_H */
