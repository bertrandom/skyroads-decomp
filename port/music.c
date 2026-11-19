/* The game's AdLib music player and Sound Blaster detection, ported from
 * the disassembly (1000:5876..1000:5bc0).  Shared by every build: the
 * platform's sound layer (audio.c natively and on the web, the Pocket's
 * firmware) provides the chip and the DMA playback:
 *   opl_out(reg, val)   write an OPL2 register
 *   opl_tick()          called once per music tick (the 180 Hz timer)
 *   sb_play / sb_stop   Sound Blaster 8-bit DMA playback
 */
#include "compat.h"
#include "protos.h"

#define DS16(off) (*(volatile uint16_t *)(g_ds + (uint16_t)(off)))
#define DS8(off)  (*(volatile uint8_t  *)(g_ds + (uint16_t)(off)))

void opl_out(uint8_t reg, uint8_t val);
void opl_tick(void);
void sb_play(const uint8_t *data, uint16_t len, uint8_t time_const);
void sb_stop(void);

/* ================================================================== */
/* music player (port of 1000:5876..1000:5a61)                         */
/* ================================================================== */
static void mus_w(uint8_t reg, uint8_t val)        /* 1000:5876 */
{
    opl_out(reg, val);
}

static void mus_keyoff(uint8_t ch)                 /* 1000:59b3 */
{
    if (ch < 6) { mus_w((uint8_t)(0xb0 + ch), 0); return; }
    {
        uint8_t cl = (uint8_t)((ch - 6) & 7);
        uint8_t ah = (uint8_t)((0xef >> cl) | (0xef << (8 - cl)));
        if (cl == 0) ah = 0xef;
        DS8(0x31a6) &= ah;
        mus_w(0xbd, DS8(0x31a6));
    }
}

static void mus_instrument(uint8_t ch, uint8_t ins) /* 1000:58fd */
{
    uint16_t si;
    int bx;
    mus_keyoff(ch);
    si = (uint16_t)(ins * 16 + DS16(0x31a0));
    DS8(0x31a7 + ch) = ins;
    for (bx = 0; bx < 5; bx++)
        mus_w((uint8_t)(DS8(0xc27 + ch) + DS8(0xc1c + bx)), DS8(si + bx));
    for (bx = 5; bx < 10; bx++) {
        unsigned r = DS8(0xc32 + ch) + DS8(0xc1c + bx);
        if (r > 0xff) continue;
        mus_w((uint8_t)r, DS8(si + bx));
    }
    if (DS8(0xc3d + ch) != 0xff)
        mus_w((uint8_t)(DS8(0xc3d + ch) + DS8(0xc1c + 10)), DS8(si + 10));
}

static void mus_note(uint8_t ch, uint8_t note)     /* 1000:5955 */
{
    mus_keyoff(ch);
    if (ch < 7) {
        uint8_t r = DS8(0xc3d + ch);
        uint8_t oct = (uint8_t)(note / 12 + 2), semi = (uint8_t)(note % 12);
        uint8_t v;
        mus_w((uint8_t)(r + 0xa0), DS8(0xc77 + semi));
        v = (uint8_t)(DS8(0xc83 + semi) | (uint8_t)(oct << 2));
        if ((uint8_t)(r + 0xb0) < 0xb6) { mus_w((uint8_t)(r + 0xb0), (uint8_t)(v | 0x20)); return; }
        mus_w((uint8_t)(r + 0xb0), v);
    }
    DS8(0x31a6) |= (uint8_t)(0x10 >> ((ch - 6) & 7));
    mus_w(0xbd, DS8(0x31a6));
}

static void mus_level(uint8_t bx, uint16_t si, uint8_t vol) /* 1000:59d3 */
{
    uint8_t v = DS8(si + 1);
    uint8_t tl = (uint8_t)((v & 0x3f) + DS8(0xc48 + vol));
    if (tl > 0x3f) tl = 0x3f;
    mus_w((uint8_t)(DS8(0xc27 + bx) + 0x40), (uint8_t)(tl | (v & 0xc0)));
}

static void mus_volume(uint8_t ch, uint8_t vol)    /* 1000:59f1 */
{
    uint16_t si = (uint16_t)(DS8(0x31a7 + ch) * 16 + DS16(0x31a0));
    if (DS8(0xc32 + ch) == 0xff) { mus_level(ch, si, vol); return; }
    mus_level((uint8_t)(ch + 0xb), (uint16_t)(si + 5), vol);
    if (DS8(si + 0xa) & 1) mus_level(ch, si, vol);
}

/* 1000:5a39  called from the timer interrupt */
void music_tick(void)
{
    int guard = 0;
    opl_tick();
    for (;;) {
        uint16_t si, w;
        uint8_t al, ah;
        if (DS8(0xc8f)) { DS8(0xc8f)--; return; }
        if (++guard > 256) return;          /* protect against garbage data */
        si = DS16(0x31a2);
        w = DS16(si);
        DS16(0x31a2) = (uint16_t)(si + 2);
        al = (uint8_t)((w & 0xff) >> 4);
        ah = (uint8_t)(w >> 8);
        switch (w & 7) {
            case 0: DS8(0xc8f) = ah; break;
            case 1: mus_instrument(al, ah); break;
            case 2: mus_note(al, ah); break;
            case 3: mus_keyoff(al); break;
            case 4: mus_volume(al, ah); break;
            case 5: DS16(0x31a2) = DS16(0x31a4); break;
            case 6: DS16(0x31a4) = DS16(0x31a2); break;
            case 7: DS8(0x31b2) = ah; break;
        }
    }
}

/* 1000:5889  silence all channels, park the player on an idle sequence */
void FUN_1000_5889(void)
{
    uint8_t r;
    int ch;
    DS16(0x31a2) = 0xcbc;
    DS8(0x31a6) = 0xe0;
    for (r = 0x40; r <= 0x55; r++) mus_w(r, 0x3f);
    for (ch = 7; ch >= 0; ch--) mus_keyoff((uint8_t)ch);
}

/* 1000:58b1  initialise the OPL and the percussion instruments */
void FUN_1000_58b1(void)
{
    int ch;
    FUN_1000_5889();
    mus_w(0x01, 0x20);
    mus_w(0x08, 0x00);
    mus_w(0xbd, 0xe0);
    DS16(0x31a0) = 0xc90;
    for (ch = 7; ch < 0xb; ch++) {
        mus_instrument((uint8_t)ch, 0);
        DS16(0x31a0) = (uint16_t)(DS16(0x31a0) + 0xb);
    }
    mus_w(0xa8, 0xac);
    mus_w(0xb8, 0x0c);
    mus_w(0xa7, 0x02);
    mus_w(0xb7, 0x0d);
}

void opl_silence(void) { FUN_1000_5889(); }

/* register-level helpers are not used directly any more */
uint8_t FUN_1000_5876(void) { return 0; }
void    FUN_1000_58fd(void) {}
void    FUN_1000_59b3(void) {}

/* 1000:5a7c  Sound Blaster detection: report a card at 220h, DMA 1 */
uint16_t FUN_1000_5a7c(void)
{
    DS16(0xcc2) = 0x220;
    DS16(0xcc4) = 1;
    return 0xd1;
}

uint32_t FUN_1000_5b1d(void) { return 0; }

/* 1000:5b5a  start DMA playback of len bytes at seg:off */
void FUN_1000_5b5a(int off, int seg, int tc, int len)
{
    if (DS16(0xcc2) == 0) return;
    sb_play(g_mem + ((uint32_t)(uint16_t)seg << 4) + (uint16_t)off, (uint16_t)len, (uint8_t)tc);
}

/* 1000:5ba4  stop DMA playback */
void FUN_1000_5ba4(void)
{
    if (DS16(0xcc2) != 0) sb_stop();
}
