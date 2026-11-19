/* Render the game's songs to WAV files, as the native build plays them.
 *
 * The same music player (music.c) and the same OPL emulation and mixing
 * as sdl/audio.c: Nuked-OPL3 (thirdparty/nuked-opl3) at 44100 Hz, buffered
 * register writes, (left + right) / 65536 * OPL_GAIN 12, the mixer's 0.18
 * and the volume's square (60 by default: 0.36), * 32000 into 16 bits,
 * mono.  The player ticks at the rate the game sets the PIT to (1193182 /
 * 6628, ~180 Hz), the writes of a tick going to the chip at that tick.
 *
 * Each song is loaded as 1000:57a8 does it: its entry in muzax.lzs's table
 * (offset, start, size), LZS-decompressed to DS:54BC, the player started at
 * start * 16 + 54BC with its instruments at 54BC.  It is rendered to the
 * jump back to its loop mark (its end) and 3 seconds more, faded out, so
 * that the loop back is heard.
 *
 * With --writes DIR, each song's OPL register writes are also saved, as
 * DIR/<name>.opl: u32 ticks (the length rendered), u32 the song's end tick,
 * then one u32 per write, tick << 16 | register << 8 | value, in order
 * (tick 0 holds the chip's set-up); the Pocket core's sim/tb_songs.cpp
 * (skyroads-pocket) plays them through the Pocket's audio hardware.
 *
 *   render_songs MUZAX.LZS OUTDIR [VOLUME] [--writes DIR]   (make songs) */
#include "compat.h"
#include "image_data.h"
#include "thirdparty/nuked-opl3/opl3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t *g_mem, *g_ds;
uint8_t g_palette[256][3];

#define DS16(off) (*(volatile uint16_t *)(g_ds + (uint16_t)(off)))
#define DS8(off)  (*(volatile uint8_t  *)(g_ds + (uint16_t)(off)))

void music_tick(void);
void FUN_1000_5889(void);
void FUN_1000_58b1(void);

#define RATE     44100
#define OPL_GAIN 12.0
#define PIT_DIV  6628.0
#define PIT_HZ   1193182.0

static opl3_chip s_chip;
static FILE *s_wr;                      /* --writes: this song's writes */
static uint32_t s_tick;
void opl_out(uint8_t reg, uint8_t val)
{
    OPL3_WriteRegBuffered(&s_chip, reg, val);
    if (s_wr) { uint32_t w = s_tick << 16 | (uint32_t)reg << 8 | val; fwrite(&w, 4, 1, s_wr); }
}
void opl_tick(void) {}
void sb_play(const uint8_t *d, uint16_t l, uint8_t t) { (void)d; (void)l; (void)t; }
void sb_stop(void) {}

/* the game's LZS (1000:6660): a header of three bytes (length bits, offset
 * bits, long offset bits), then a bit stream, most significant bit first */
static int lzs(const uint8_t *src, size_t n, uint8_t *dst, uint32_t size)
{
    size_t p = 0;
    uint32_t byte, bits = 8, di = 0, len_bits, off_bits, long_bits, long_add;
#define NEXT() (p < n ? src[p++] : 0)
#define BIT() ({ uint32_t b_ = (byte >> 7) & 1; byte = (byte << 1) & 0xff; \
                 if (--bits == 0) { bits = 8; byte = NEXT(); } b_; })
    if (n < 4) return -1;
    len_bits = NEXT(); off_bits = NEXT(); long_bits = NEXT();
    long_add = 1u << (off_bits & 0x1f);
    byte = NEXT();
    while (di < size) {
        uint32_t offset = 0, len = 0, k, si, count;
        if (BIT() == 0) { for (k = 0; k < off_bits; k++) offset = offset << 1 | BIT(); }
        else if (BIT() == 0) { for (k = 0; k < long_bits; k++) offset = offset << 1 | BIT(); offset += long_add; }
        else {
            uint32_t lit = 0;
            for (k = 0; k < 8; k++) lit = lit << 1 | BIT();
            dst[di++] = (uint8_t)lit;
            continue;
        }
        for (k = 0; k < len_bits; k++) len = len << 1 | BIT();
        if (len + 1 >= size - di) break;
        si = di - 2 - offset;
        count = len + 2;
        while (count-- && di < size) dst[di++] = dst[si++];
    }
    return (int)di;
#undef NEXT
#undef BIT
}

static void wav_header(FILE *f, uint32_t samples)
{
    uint32_t data = samples * 2, v;
    fwrite("RIFF", 1, 4, f); v = 36 + data; fwrite(&v, 4, 1, f);
    fwrite("WAVEfmt ", 1, 8, f);
    v = 16; fwrite(&v, 4, 1, f);
    uint16_t fmt = 1, ch = 1, align = 2, bps = 16;
    fwrite(&fmt, 2, 1, f); fwrite(&ch, 2, 1, f);
    v = RATE; fwrite(&v, 4, 1, f); v = RATE * 2; fwrite(&v, 4, 1, f);
    fwrite(&align, 2, 1, f); fwrite(&bps, 2, 1, f);
    fwrite("data", 1, 4, f); fwrite(&data, 4, 1, f);
}

static void song_name(char *out, size_t n, int i)
{
    if (i == 0) snprintf(out, n, "00 Title");
    else if (i == 1) snprintf(out, n, "01 Menu");
    else snprintf(out, n, "%02d Road song %d", i, i - 1);
}

int main(int argc, char **argv)
{
    FILE *f;
    uint8_t *muz;
    long nmuz;
    int volume = 60, nsongs, i, a;
    const char *wdir = NULL;
    double gain;
    for (a = 3; a < argc; a++) {
        if (!strcmp(argv[a], "--writes") && a + 1 < argc) wdir = argv[++a];
        else volume = atoi(argv[a]);
    }
    gain = (volume / 100.0) * (volume / 100.0);
    if (argc < 3) { fprintf(stderr, "usage: render_songs MUZAX.LZS OUTDIR [VOLUME]\n"); return 1; }
    if (!(f = fopen(argv[1], "rb"))) { perror(argv[1]); return 1; }
    fseek(f, 0, SEEK_END); nmuz = ftell(f); fseek(f, 0, SEEK_SET);
    muz = malloc((size_t)nmuz);
    if (fread(muz, 1, (size_t)nmuz, f) != (size_t)nmuz) { perror(argv[1]); return 1; }
    fclose(f);
    nsongs = (muz[0] | muz[1] << 8) / 6;

    for (i = 0; i < nsongs; i++) {
        const uint8_t *e = muz + i * 6;
        uint16_t off = e[0] | e[1] << 8, mid = e[2] | e[3] << 8, size = e[4] | e[5] << 8;
        uint16_t start, si;
        uint32_t len = 0, loop = 0, k, total, tick, fade, peak = 0, clipped = 0, written = 0;
        double acc = 0, per_tick = RATE * PIT_DIV / PIT_HZ;
        char name[64], path[512];
        if (size == 0) break;                       /* the empty entries at the end */

        song_name(name, sizeof name, i);
        if (wdir) {
            uint32_t zero = 0;
            snprintf(path, sizeof path, "%s/%s.opl", wdir, name);
            if (!(s_wr = fopen(path, "wb"))) { perror(path); return 1; }
            fwrite(&zero, 4, 1, s_wr); fwrite(&zero, 4, 1, s_wr);
        }
        s_tick = 0;
        g_mem = calloc(1, MEM_SIZE);
        memcpy(g_mem + CS_BASE, skyroads_image, sizeof skyroads_image);
        g_ds = g_mem + DS_BASE;
        OPL3_Reset(&s_chip, RATE);
        FUN_1000_58b1();                            /* the chip, as the game starts */
        FUN_1000_5889();                            /* 1000:57a8: silence, then load */
        if (lzs(muz + off, (size_t)(nmuz - off), g_ds + 0x54bc, size) < 0) { fprintf(stderr, "song %d: bad data\n", i); return 1; }
        start = (uint16_t)(mid * 0x10 + 0x54bc);
        DS16(0x31a2) = start; DS16(0x31a4) = start; DS16(0x31a0) = 0x54bc; DS8(0x31b2) = 0;

        /* its length: the delays up to the jump back (the end) */
        for (si = start, k = 0; k < 200000; k++) {
            uint16_t w = DS16(si);
            si = (uint16_t)(si + 2);
            if ((w & 7) == 0) len += w >> 8;
            else if ((w & 7) == 6) loop = len;
            else if ((w & 7) == 5) break;
        }
        fade = (uint32_t)(3 * PIT_HZ / PIT_DIV);
        total = len + fade;

        snprintf(path, sizeof path, "%s/%s.wav", argv[2], name);
        if (!(f = fopen(path, "wb"))) { perror(path); return 1; }
        wav_header(f, 0);
        for (tick = 0; tick < total; tick++) {
            int n;
            s_tick = tick;
            music_tick();
            acc += per_tick;
            n = (int)acc;
            acc -= n;
            while (n--) {
                int16_t lr[2], s;
                double v, fg = tick < len ? 1.0 : 1.0 - (double)(tick - len) / fade;
                OPL3_GenerateResampled(&s_chip, lr);
                v = (lr[0] + lr[1]) / 65536.0 * OPL_GAIN * 0.18 * gain * fg;
                if (v > 1) { v = 1; clipped++; }
                if (v < -1) { v = -1; clipped++; }
                s = (int16_t)(v * 32000);
                if ((uint32_t)abs(s) > peak) peak = (uint32_t)abs(s);
                fwrite(&s, 2, 1, f);
                written++;
            }
        }
        fseek(f, 0, SEEK_SET);
        wav_header(f, written);
        fclose(f);
        if (s_wr) {
            fseek(s_wr, 0, SEEK_SET);
            fwrite(&total, 4, 1, s_wr); fwrite(&len, 4, 1, s_wr);
            fclose(s_wr);
            s_wr = NULL;
        }
        printf("%-18s %2u:%02u  loops to %u:%02u  peak %5.1f%%%s\n", name,
               (unsigned)(len * PIT_DIV / PIT_HZ) / 60, (unsigned)(len * PIT_DIV / PIT_HZ) % 60,
               (unsigned)(loop * PIT_DIV / PIT_HZ) / 60, (unsigned)(loop * PIT_DIV / PIT_HZ) % 60,
               peak * 100.0 / 32000, clipped ? "  (clipped)" : "");
        free(g_mem);
    }
    return 0;
}
