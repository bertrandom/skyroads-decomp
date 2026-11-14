/* Sound: AdLib (OPL2) music, Sound Blaster digitised effects, PC speaker.
 *
 * - opl_*: the AdLib chip, emulated by Nuked-OPL3 (thirdparty/nuked-opl3).
 * - mus_*: C port of the game's music player (1000:5876..1000:5a61).  The
 *   timer interrupt calls music_tick() at ~180 Hz like the original.
 * - sb_*: Sound Blaster 8-bit DMA playback (1000:5b1d/5b76/5bc0).
 * - speaker_*: PC speaker square wave (channel 2 of the PIT).
 */
#include "compat.h"
#include "protos.h"
#include <math.h>
#include <SDL.h>

#define DS16(off) (*(volatile uint16_t *)(g_ds + (uint16_t)(off)))
#define DS8(off)  (*(volatile uint8_t  *)(g_ds + (uint16_t)(off)))

#define RATE 44100

static SDL_AudioDeviceID s_dev;

/* ================================================================== */
/* OPL2 emulation: Nuked-OPL3 (thirdparty/nuked-opl3, LGPL-2.1), a       */
/* cycle-accurate YMF262 model, which runs the game's OPL2 register       */
/* writes in its OPL2-compatible mode (both outputs carry every channel). */
/* ================================================================== */
#include "thirdparty/nuked-opl3/opl3.h"

#define OPL_GAIN 12.0  /* music level as before, relative to the Sound Blaster effects */
static opl3_chip s_opl;
static int s_opl_ready;

static void opl_init(void)
{
    if (!s_opl_ready) { OPL3_Reset(&s_opl, RATE); s_opl_ready = 1; }
}

/* Buffered: Nuked applies each write a couple of chip samples after the
 * previous one, like the real chip behind the player's port delays.  The
 * player restarts a note by keying it off and straight back on (B0+ch, and
 * the drum bits in BD); written at once, the chip never sees the key off and
 * the note does not sound again. */
static void opl_write(uint8_t reg, uint8_t val)
{
    opl_init();
    OPL3_WriteRegBuffered(&s_opl, reg, val);
}

static double opl_sample(void)
{
    int16_t lr[2];
    OPL3_GenerateResampled(&s_opl, lr);  /* 49716 Hz chip -> RATE */
    return (lr[0] + lr[1]) / 65536.0 * OPL_GAIN;
}

/* ================================================================== */
/* Sound Blaster / PC speaker                                          */
/* ================================================================== */
static const uint8_t *s_sb_data;
static uint32_t s_sb_len;
static double s_sb_pos, s_sb_step;

static volatile int s_spk_gate;
static volatile uint16_t s_spk_div;
static double s_spk_phase;

#ifdef __EMSCRIPTEN__
/* The browser renders audio on the main thread and SDL's device lock is a
 * no-op there, so OPL register writes from the timer thread go through a
 * single-producer/single-consumer queue stamped with the timer tick; the
 * synthesizer applies them at the matching sample, a fixed latency behind. */
#include <stdatomic.h>
#include <emscripten.h>
#define OPLQ 4096
typedef struct { uint32_t tick; uint8_t reg, val; } OplEvt;
static OplEvt s_q[OPLQ];
static atomic_uint s_q_w, s_q_r;
static atomic_uint s_tick;          /* music ticks (180 Hz) */
static double s_synth_tick = -1;    /* tick position of the next sample */
#define TICK_SAMPLES (RATE / 180.0)
#define LATENCY_TICKS 16.0

/* The page suspends the audio output while the sound is off, and the music
 * plays on unheard.  Meanwhile the writes are only remembered here (the
 * last value of each register) and written to the chip when the output
 * comes back, so the song continues where it is. */
static volatile uint8_t s_shadow[256], s_shadow_set[256];
static atomic_int s_out_muted;

static void oplq_push(uint8_t reg, uint8_t val)
{
    unsigned w;
    s_shadow[reg] = val;
    s_shadow_set[reg] = 1;
    if (atomic_load_explicit(&s_out_muted, memory_order_acquire)) return;
    w = atomic_load_explicit(&s_q_w, memory_order_relaxed);
    if (w - atomic_load_explicit(&s_q_r, memory_order_acquire) >= OPLQ) return;
    s_q[w % OPLQ].tick = atomic_load_explicit(&s_tick, memory_order_relaxed);
    s_q[w % OPLQ].reg = reg;
    s_q[w % OPLQ].val = val;
    atomic_store_explicit(&s_q_w, w + 1, memory_order_release);
}

static void oplq_apply(void)
{
    unsigned r = atomic_load_explicit(&s_q_r, memory_order_relaxed);
    unsigned w = atomic_load_explicit(&s_q_w, memory_order_acquire);
    double now = (double)atomic_load_explicit(&s_tick, memory_order_relaxed);
    /* keep the synth clock LATENCY_TICKS behind the music clock */
    if (s_synth_tick < 0 || s_synth_tick > now || s_synth_tick < now - 4 * LATENCY_TICKS)
        s_synth_tick = now - LATENCY_TICKS;
    while (r != w && (double)s_q[r % OPLQ].tick <= s_synth_tick) {
        opl_write(s_q[r % OPLQ].reg, s_q[r % OPLQ].val);
        r++;
    }
    atomic_store_explicit(&s_q_r, r, memory_order_release);
}

/* main thread, which also runs the audio callback (so it is not running) */
EMSCRIPTEN_KEEPALIVE void sky_audio_mute(int mute)
{
    int pass, reg;
    if (mute) { atomic_store(&s_out_muted, 1); return; }
    if (!atomic_exchange(&s_out_muted, 0)) return;
    /* drop what was queued before the mute, then bring the chip up to date:
     * instruments and pitches first, then the key-on registers (a write
     * also queued since is applied again, which changes nothing) */
    atomic_store(&s_q_r, atomic_load(&s_q_w));
    for (pass = 0; pass < 2; pass++)
        for (reg = 0; reg < 256; reg++) {
            int key = (reg >= 0xb0 && reg <= 0xb8) || reg == 0xbd;
            if (s_shadow_set[reg] && key == pass) opl_write((uint8_t)reg, s_shadow[reg]);
        }
    s_synth_tick = -1;
}
#endif

static void audio_cb(void *ud, Uint8 *stream, int len)
{
    int16_t *out = (int16_t *)stream;
    int i, n = len / 2;
    (void)ud;
    for (i = 0; i < n; i++) {
        double v;
#ifdef __EMSCRIPTEN__
        if ((i & 31) == 0) oplq_apply();
        s_synth_tick += 1.0 / TICK_SAMPLES;
#endif
        v = opl_sample() * 0.18;
        if (s_sb_data) {
            uint32_t p = (uint32_t)s_sb_pos;
            if (p < s_sb_len) {
                v += ((int)s_sb_data[p] - 128) / 128.0 * 0.55;
                s_sb_pos += s_sb_step;
            } else s_sb_data = NULL;
        }
        if (s_spk_gate && s_spk_div > 40) {
            double f = 1193182.0 / s_spk_div;
            s_spk_phase += f / RATE;
            s_spk_phase -= floor(s_spk_phase);
            v += (s_spk_phase < 0.5 ? 0.12 : -0.12);
        }
        if (v > 1) v = 1;
        if (v < -1) v = -1;
        out[i] = (int16_t)(v * 32000);
    }
    {   /* debug: SKY_WAV=file.raw dumps the mix (s16le mono 44100) */
        static FILE *wav; static int tried;
        if (!tried) { const char *p = getenv("SKY_WAV"); tried = 1; if (p) wav = fopen(p, "wb"); }
        if (wav) fwrite(stream, 1, len, wav);
    }
}

void snd_init(void)
{
    SDL_AudioSpec want, have;
    opl_init();
    SDL_zero(want);
    want.freq = RATE;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
#ifdef __EMSCRIPTEN__
    want.samples = 2048;
#else
    want.samples = 1024;
#endif
    want.callback = audio_cb;
    s_dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (s_dev) SDL_PauseAudioDevice(s_dev, 0);
    else fprintf(stderr, "audio: %s\n", SDL_GetError());
}

static void lock(void)   { if (s_dev) SDL_LockAudioDevice(s_dev); }
static void unlock(void) { if (s_dev) SDL_UnlockAudioDevice(s_dev); }

void sb_play(const uint8_t *data, uint16_t len, uint8_t time_const)
{
    double rate = 1000000.0 / (256 - time_const);
    lock();
    s_sb_data = data;
    s_sb_len = len;
    s_sb_pos = 0;
    s_sb_step = rate / RATE;
    unlock();
}

void sb_stop(void)
{
    lock();
    s_sb_data = NULL;
    unlock();
}

void speaker_set_divisor(uint16_t div) { s_spk_div = div; }
void speaker_gate(int on) { s_spk_gate = on; }
void snd_speaker_on(uint16_t div) { (void)div; speaker_gate(1); }
void snd_speaker_off(void) { speaker_gate(0); }
void snd_write_dac(uint8_t s) { (void)s; }
void snd_pause(void) { if (s_dev) SDL_PauseAudioDevice(s_dev, 1); }

/* ================================================================== */
/* music player (port of 1000:5876..1000:5a61)                         */
/* ================================================================== */
static void mus_w(uint8_t reg, uint8_t val)        /* 1000:5876 */
{
#ifdef __EMSCRIPTEN__
    oplq_push(reg, val);
#else
    lock();
    opl_write(reg, val);
    unlock();
#endif
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
#ifdef __EMSCRIPTEN__
    atomic_fetch_add_explicit(&s_tick, 1, memory_order_relaxed);
#endif
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
