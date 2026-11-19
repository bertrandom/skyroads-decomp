/* Sound: AdLib (OPL2) music, Sound Blaster digitised effects, PC speaker.
 *
 * - opl_*: the AdLib chip, emulated by Nuked-OPL3 (thirdparty/nuked-opl3).
 * - the game's music player (1000:5876..1000:5a61) is in music.c; the
 *   timer interrupt calls its music_tick() at ~180 Hz like the original.
 * - sb_*: Sound Blaster 8-bit DMA playback (1000:5b1d/5b76/5bc0).
 * - speaker_*: PC speaker square wave (channel 2 of the PIT).
 */
#include "compat.h"
#include "protos.h"
#include <math.h>
#include <stdatomic.h>
#include <SDL.h>

/* The volume, 1-100 (the page's slider, natively the - and = keys): the mix
 * is scaled by (volume / 100)^2, so 100 is full scale (the music's peaks
 * near it) and the default, 60, about 9 dB below. */
static atomic_int s_volume = 60;
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
EMSCRIPTEN_KEEPALIVE
#endif
void sky_set_volume(int v) { atomic_store(&s_volume, v < 0 ? 0 : v > 100 ? 100 : v); }
#ifdef __EMSCRIPTEN__
EMSCRIPTEN_KEEPALIVE
#endif
int sky_volume(void) { return atomic_load(&s_volume); }

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
    double gain = atomic_load(&s_volume) / 100.0;
    (void)ud;
    gain *= gain;
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
        v *= gain;
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
/* the music player's (music.c) hooks                                   */
/* ================================================================== */
void opl_out(uint8_t reg, uint8_t val)
{
#ifdef __EMSCRIPTEN__
    oplq_push(reg, val);
#else
    lock();
    opl_write(reg, val);
    unlock();
#endif
}

void opl_tick(void)
{
#ifdef __EMSCRIPTEN__
    atomic_fetch_add_explicit(&s_tick, 1, memory_order_relaxed);
#endif
}
