/* Sound: AdLib (OPL2) music, Sound Blaster digitised effects, PC speaker.
 *
 * - opl_*: a compact software YM3812 (OPL2) good enough for the game's
 *   instruments (2-op FM, ADSR, KSL, feedback, waveforms, tremolo/vibrato,
 *   rhythm mode).
 * - mus_*: C port of the game's music player (1000:5892..1000:5a7d).  The
 *   timer interrupt calls music_tick() at ~180 Hz like the original.
 * - sb_*: Sound Blaster 8-bit DMA playback (1000:5b39/5b76/5bc0).
 * - speaker_*: PC speaker square wave (channel 2 of the PIT).
 */
#include "compat.h"
#include <math.h>
#include <SDL.h>

#define DS16(off) (*(volatile uint16_t *)(g_ds + (uint16_t)(off)))
#define DS8(off)  (*(volatile uint8_t  *)(g_ds + (uint16_t)(off)))

#define RATE 44100
#define OPL_CLOCK_RATE 49716.0

static SDL_AudioDeviceID s_dev;

/* ================================================================== */
/* OPL2 emulation                                                      */
/* ================================================================== */
typedef struct {
    /* registers */
    uint8_t am, vib, egt, ksr, mult, ksl, tl, ar, dr, sl, rr, ws;
    /* state */
    double phase;          /* cycles */
    double env;            /* attenuation in dB (0 loud .. 96 silent) */
    int stage;             /* 0 off, 1 attack, 2 decay, 3 sustain, 4 release */
    double out1, out2;     /* last outputs (feedback) */
} Op;

typedef struct {
    uint16_t fnum;
    uint8_t block, keyon, fb, cnt;
} Chan;

static Op   s_op[18];
static Chan s_ch[9];
static uint8_t s_reg_bd, s_wse;
static double s_am_phase, s_vib_phase;
static uint32_t s_noise = 1;

/* operator register offset -> operator index (-1 = none) */
static const int8_t k_slot[32] = {
    0, 1, 2, 3, 4, 5, -1, -1, 6, 7, 8, 9, 10, 11, -1, -1,
    12, 13, 14, 15, 16, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
/* channel -> modulator / carrier operator index */
static const int k_mod[9] = { 0, 1, 2, 6, 7, 8, 12, 13, 14 };
static const int k_car[9] = { 3, 4, 5, 9, 10, 11, 15, 16, 17 };
static const double k_mult[16] = { 0.5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 12, 12, 15, 15 };
static const double k_ksl[16] = { 0, 18, 24, 27.75, 30, 32.25, 33.75, 35.25,
                                  36, 37.5, 38.25, 39, 39.75, 40.5, 41.25, 42 };

static int op_chan(int op)
{
    int c;
    for (c = 0; c < 9; c++) if (k_mod[c] == op || k_car[c] == op) return c;
    return 0;
}

static void op_keyon(Op *o)
{
    if (o->stage == 0 || o->stage == 4) {
        o->phase = 0;
        o->stage = 1;
    }
}

static void op_keyoff(Op *o)
{
    if (o->stage != 0) o->stage = 4;
}

static void opl_write(uint8_t reg, uint8_t val)
{
    int op;
    if (reg == 0x01) { s_wse = val & 0x20; return; }
    if (reg == 0xbd) {
        uint8_t old = s_reg_bd;
        s_reg_bd = val;
        if (val & 0x20) {
            /* rhythm: BD=ch6 both ops, SD=op16, TOM=op14, CY=op17, HH=op13 */
            struct { uint8_t bit; int ops[2]; } r[5] = {
                { 0x10, { 12, 15 } }, { 0x08, { 16, -1 } }, { 0x04, { 14, -1 } },
                { 0x02, { 17, -1 } }, { 0x01, { 13, -1 } } };
            int i, k;
            for (i = 0; i < 5; i++) {
                int on = (val & r[i].bit) != 0, was = (old & 0x20) && (old & r[i].bit);
                for (k = 0; k < 2; k++) {
                    if (r[i].ops[k] < 0) continue;
                    if (on && !was) op_keyon(&s_op[r[i].ops[k]]);
                    if (!on && was) op_keyoff(&s_op[r[i].ops[k]]);
                }
            }
        }
        return;
    }
    if (reg >= 0x20 && reg < 0xa0) {
        op = k_slot[reg & 0x1f];
        if (op < 0) return;
        switch (reg & 0xe0) {
            case 0x20:
                s_op[op].am = (val >> 7) & 1; s_op[op].vib = (val >> 6) & 1;
                s_op[op].egt = (val >> 5) & 1; s_op[op].ksr = (val >> 4) & 1;
                s_op[op].mult = val & 15; break;
            case 0x40: s_op[op].ksl = val >> 6; s_op[op].tl = val & 0x3f; break;
            case 0x60: s_op[op].ar = val >> 4; s_op[op].dr = val & 15; break;
            case 0x80: s_op[op].sl = val >> 4; s_op[op].rr = val & 15; break;
        }
        return;
    }
    if (reg >= 0xe0 && reg < 0xf6) {
        op = k_slot[reg & 0x1f];
        if (op >= 0) s_op[op].ws = val & 3;
        return;
    }
    if (reg >= 0xa0 && reg <= 0xa8) { s_ch[reg - 0xa0].fnum = (uint16_t)((s_ch[reg - 0xa0].fnum & 0x300) | val); return; }
    if (reg >= 0xb0 && reg <= 0xb8) {
        Chan *c = &s_ch[reg - 0xb0];
        int on = (val >> 5) & 1, ch = reg - 0xb0;
        c->fnum = (uint16_t)((c->fnum & 0xff) | ((val & 3) << 8));
        c->block = (val >> 2) & 7;
        if (on && !c->keyon) { op_keyon(&s_op[k_mod[ch]]); op_keyon(&s_op[k_car[ch]]); }
        if (!on && c->keyon) { op_keyoff(&s_op[k_mod[ch]]); op_keyoff(&s_op[k_car[ch]]); }
        c->keyon = (uint8_t)on;
        return;
    }
    if (reg >= 0xc0 && reg <= 0xc8) {
        s_ch[reg - 0xc0].fb = (val >> 1) & 7;
        s_ch[reg - 0xc0].cnt = val & 1;
    }
}

/* time (seconds) for a full 96 dB decay at effective rate */
static double eg_step(int rate4, double full_time_s)
{
    double t;
    if (rate4 < 4) return 0;
    if (rate4 > 60) rate4 = 60;
    t = full_time_s / pow(2.0, (rate4 - 4) / 4.0);
    return 96.0 / (t * RATE);
}

static void op_envelope(Op *o, const Chan *c)
{
    int rof = (c->block << 1) | ((c->fnum >> 9) & 1);
    if (!o->ksr) rof >>= 2;
    switch (o->stage) {
        case 1: {
            double step;
            if (o->ar == 15) { o->env = 0; o->stage = 2; break; }
            step = eg_step(o->ar * 4 + rof, 2.826 * 1.0);
            if (step == 0) break;
            /* exponential attack */
            o->env -= step * (1.0 + o->env / 12.0);
            if (o->env <= 0) { o->env = 0; o->stage = 2; }
            break;
        }
        case 2: {
            double sl = (o->sl == 15) ? 93.0 : o->sl * 3.0;
            o->env += eg_step(o->dr * 4 + rof, 39.28);
            if (o->env >= sl) { o->env = sl; o->stage = 3; }
            break;
        }
        case 3:
            if (!o->egt) o->env += eg_step(o->rr * 4 + rof, 39.28);
            break;
        case 4:
            o->env += eg_step(o->rr * 4 + rof, 39.28);
            break;
        default: break;
    }
    if (o->env >= 96.0) { o->env = 96.0; if (o->stage >= 3) o->stage = 0; }
}

static double wave(int ws, double ph)
{
    double s;
    ph -= floor(ph);
    s = sin(ph * 2.0 * M_PI);
    if (!s_wse) return s;
    switch (ws) {
        case 1: return s > 0 ? s : 0;
        case 2: return fabs(s);
        case 3: return (fmod(ph, 0.5) < 0.25) ? fabs(s) : 0;
        default: return s;
    }
}

static double op_level(const Op *o, const Chan *c, double am)
{
    double att = o->env + o->tl * 0.75;
    if (o->ksl) {
        double k = k_ksl[c->fnum >> 6] - 6.0 * (7 - c->block);
        if (k > 0) att += k * (o->ksl == 1 ? 0.5 : o->ksl == 2 ? 0.25 : 1.0);
    }
    if (o->am) att += am;
    if (att >= 96.0) return 0;
    return pow(10.0, -att / 20.0);
}

static double op_freq(const Op *o, const Chan *c, double vib)
{
    double f = c->fnum * OPL_CLOCK_RATE / (double)(1 << (20 - c->block)) * k_mult[o->mult];
    if (o->vib) f *= vib;
    return f;
}

static double op_run(Op *o, const Chan *c, double mod, double am, double vib)
{
    double lvl, out;
    op_envelope(o, c);
    if (o->stage == 0) { o->out2 = o->out1; o->out1 = 0; return 0; }
    lvl = op_level(o, c, am);
    out = wave(o->ws, o->phase + mod) * lvl;
    o->phase += op_freq(o, c, vib) / RATE;
    if (o->phase > 1e6) o->phase -= floor(o->phase);
    o->out2 = o->out1;
    o->out1 = out;
    return out;
}

static double opl_sample(void)
{
    double am, vib, sum = 0;
    int ch, rhythm = (s_reg_bd & 0x20) != 0;
    s_am_phase += 3.7 / RATE;
    s_vib_phase += 6.1 / RATE;
    am = (1.0 + sin(s_am_phase * 2 * M_PI)) * 0.5 * ((s_reg_bd & 0x80) ? 4.8 : 1.0);
    vib = pow(2.0, sin(s_vib_phase * 2 * M_PI) * ((s_reg_bd & 0x40) ? 14.0 : 7.0) / 1200.0);
    s_noise = (s_noise >> 1) ^ ((s_noise & 1) ? 0x400181 : 0);

    for (ch = 0; ch < 9; ch++) {
        Chan *c = &s_ch[ch];
        Op *m = &s_op[k_mod[ch]], *k = &s_op[k_car[ch]];
        double fb, mo;
        if (rhythm && ch >= 6) continue;
        fb = c->fb ? (m->out1 + m->out2) * 0.5 * pow(2.0, c->fb - 7) * 2.0 : 0;
        mo = op_run(m, c, fb, am, vib);
        if (c->cnt) sum += mo + op_run(k, c, 0, am, vib);
        else sum += op_run(k, c, mo * 4.0, am, vib);
    }
    if (rhythm) {
        Chan *c6 = &s_ch[6], *c7 = &s_ch[7], *c8 = &s_ch[8];
        Op *bdm = &s_op[12], *bdc = &s_op[15];
        double fb = c6->fb ? (bdm->out1 + bdm->out2) * 0.5 * pow(2.0, c6->fb - 7) * 2.0 : 0;
        double mo = op_run(bdm, c6, fb, am, vib);
        double noise = (s_noise & 1) ? 1.0 : -1.0;
        sum += 2.0 * (c6->cnt ? op_run(bdc, c6, 0, am, vib) : op_run(bdc, c6, mo * 4.0, am, vib));
        /* hi-hat (op13) and snare (op16) on channel 7, tom (op14) and cymbal (op17) on 8 */
        {
            Op *hh = &s_op[13], *sd = &s_op[16], *tt = &s_op[14], *cy = &s_op[17];
            double h = op_run(hh, c7, 0, am, vib);
            double s = op_run(sd, c7, 0, am, vib);
            double t = op_run(tt, c8, 0, am, vib);
            double y = op_run(cy, c8, 0, am, vib);
            /* replace tonal output with noisier versions, keeping envelopes */
            if (hh->stage) h = (h > 0 ? 1 : -1) * fabs(h) * 0.5 + noise * op_level(hh, c7, am) * 0.5;
            if (sd->stage) s = s * 0.5 + noise * op_level(sd, c7, am) * 0.5;
            if (cy->stage) y = (y > 0 ? 1.0 : -1.0) * op_level(cy, c8, am) * 0.7;
            sum += 2.0 * (h + s + t + y);
        }
    }
    return sum;
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

static void audio_cb(void *ud, Uint8 *stream, int len)
{
    int16_t *out = (int16_t *)stream;
    int i, n = len / 2;
    (void)ud;
    for (i = 0; i < n; i++) {
        double v = opl_sample() * 0.18;
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
    SDL_zero(want);
    want.freq = RATE;
    want.format = AUDIO_S16SYS;
    want.channels = 1;
    want.samples = 1024;
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

/* ================================================================== */
/* music player (port of 1000:5892..1000:5a7d)                         */
/* ================================================================== */
static void mus_w(uint8_t reg, uint8_t val)        /* 1000:5892 */
{
    lock();
    opl_write(reg, val);
    unlock();
}

static void mus_keyoff(uint8_t ch)                 /* 1000:59cf */
{
    if (ch < 6) { mus_w((uint8_t)(0xb0 + ch), 0); return; }
    {
        uint8_t cl = (uint8_t)((ch - 6) & 7);
        uint8_t ah = (uint8_t)((0xef >> cl) | (0xef << (8 - cl)));
        if (cl == 0) ah = 0xef;
        DS8(0x319a) &= ah;
        mus_w(0xbd, DS8(0x319a));
    }
}

static void mus_instrument(uint8_t ch, uint8_t ins) /* 1000:5919 */
{
    uint16_t si;
    int bx;
    mus_keyoff(ch);
    si = (uint16_t)(ins * 16 + DS16(0x3194));
    DS8(0x319b + ch) = ins;
    for (bx = 0; bx < 5; bx++)
        mus_w((uint8_t)(DS8(0xc1b + ch) + DS8(0xc10 + bx)), DS8(si + bx));
    for (bx = 5; bx < 10; bx++) {
        unsigned r = DS8(0xc26 + ch) + DS8(0xc10 + bx);
        if (r > 0xff) continue;
        mus_w((uint8_t)r, DS8(si + bx));
    }
    if (DS8(0xc31 + ch) != 0xff)
        mus_w((uint8_t)(DS8(0xc31 + ch) + DS8(0xc10 + 10)), DS8(si + 10));
}

static void mus_note(uint8_t ch, uint8_t note)     /* 1000:5971 */
{
    mus_keyoff(ch);
    if (ch < 7) {
        uint8_t r = DS8(0xc31 + ch);
        uint8_t oct = (uint8_t)(note / 12 + 2), semi = (uint8_t)(note % 12);
        uint8_t v;
        mus_w((uint8_t)(r + 0xa0), DS8(0xc6b + semi));
        v = (uint8_t)(DS8(0xc77 + semi) | (uint8_t)(oct << 2));
        if ((uint8_t)(r + 0xb0) < 0xb6) { mus_w((uint8_t)(r + 0xb0), (uint8_t)(v | 0x20)); return; }
        mus_w((uint8_t)(r + 0xb0), v);
    }
    DS8(0x319a) |= (uint8_t)(0x10 >> ((ch - 6) & 7));
    mus_w(0xbd, DS8(0x319a));
}

static void mus_level(uint8_t bx, uint16_t si, uint8_t vol) /* 1000:59ef */
{
    uint8_t v = DS8(si + 1);
    uint8_t tl = (uint8_t)((v & 0x3f) + DS8(0xc3c + vol));
    if (tl > 0x3f) tl = 0x3f;
    mus_w((uint8_t)(DS8(0xc1b + bx) + 0x40), (uint8_t)(tl | (v & 0xc0)));
}

static void mus_volume(uint8_t ch, uint8_t vol)    /* 1000:5a0d */
{
    uint16_t si = (uint16_t)(DS8(0x319b + ch) * 16 + DS16(0x3194));
    if (DS8(0xc26 + ch) == 0xff) { mus_level(ch, si, vol); return; }
    mus_level((uint8_t)(ch + 0xb), (uint16_t)(si + 5), vol);
    if (DS8(si + 0xa) & 1) mus_level(ch, si, vol);
}

/* 1000:5a55  called from the timer interrupt */
void music_tick(void)
{
    int guard = 0;
    for (;;) {
        uint16_t si, w;
        uint8_t al, ah;
        if (DS8(0xc83)) { DS8(0xc83)--; return; }
        if (++guard > 256) return;          /* protect against garbage data */
        si = DS16(0x3196);
        w = DS16(si);
        DS16(0x3196) = (uint16_t)(si + 2);
        al = (uint8_t)((w & 0xff) >> 4);
        ah = (uint8_t)(w >> 8);
        switch (w & 7) {
            case 0: DS8(0xc83) = ah; break;
            case 1: mus_instrument(al, ah); break;
            case 2: mus_note(al, ah); break;
            case 3: mus_keyoff(al); break;
            case 4: mus_volume(al, ah); break;
            case 5: DS16(0x3196) = DS16(0x3198); break;
            case 6: DS16(0x3198) = DS16(0x3196); break;
            case 7: DS8(0x31a6) = ah; break;
        }
    }
}

/* 1000:58a5  silence all channels, park the player on an idle sequence */
void FUN_1000_58a5(void)
{
    uint8_t r;
    int ch;
    DS16(0x3196) = 0xcb0;
    DS8(0x319a) = 0xe0;
    for (r = 0x40; r <= 0x55; r++) mus_w(r, 0x3f);
    for (ch = 7; ch >= 0; ch--) mus_keyoff((uint8_t)ch);
}

/* 1000:58cd  initialise the OPL and the percussion instruments */
void FUN_1000_58cd(void)
{
    int ch;
    FUN_1000_58a5();
    mus_w(0x01, 0x20);
    mus_w(0x08, 0x00);
    mus_w(0xbd, 0xe0);
    DS16(0x3194) = 0xc84;
    for (ch = 7; ch < 0xb; ch++) {
        mus_instrument((uint8_t)ch, 0);
        DS16(0x3194) = (uint16_t)(DS16(0x3194) + 0xb);
    }
    mus_w(0xa8, 0xac);
    mus_w(0xb8, 0x0c);
    mus_w(0xa7, 0x02);
    mus_w(0xb7, 0x0d);
}

void opl_silence(void) { FUN_1000_58a5(); }

/* register-level helpers are not used directly any more */
uint8_t FUN_1000_5892(void) { return 0; }
void    FUN_1000_5919(void) {}
void    FUN_1000_59cf(void) {}

/* 1000:5a98  Sound Blaster detection: report a card at 220h, DMA 1 */
uint16_t FUN_1000_5a98(void)
{
    DS16(0xcb6) = 0x220;
    DS16(0xcb8) = 1;
    return 0xd1;
}

uint32_t FUN_1000_5b39(void) { return 0; }

/* 1000:5b76  start DMA playback of len bytes at seg:off */
void FUN_1000_5b76(int off, int seg, int tc, int len)
{
    if (DS16(0xcb6) == 0) return;
    sb_play(g_mem + ((uint32_t)(uint16_t)seg << 4) + (uint16_t)off, (uint16_t)len, (uint8_t)tc);
}

/* 1000:5bc0  stop DMA playback */
void FUN_1000_5bc0(void)
{
    if (DS16(0xcb6) != 0) sb_stop();
}
