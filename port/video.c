/* VGA compatibility layer and the hand ported rasteriser.
 *
 * The original renders into a 320x200 8-bit framebuffer (mode 13h) and a set
 * of scratch buffers in the data segment.  We keep a software model of the
 * Graphics Controller registers so the ported code (and any remaining
 * register-level helpers) behave like the original. */
#include "compat.h"
#include "protos.h"
#define DS16(off) (*(uint16_t *)(g_ds + (off)))

/* Graphics controller / sequencer / DAC state. */
static uint8_t gc_index, gc_regs[16];
static uint8_t seq_index, seq_regs[8];
static uint8_t dac_index, dac_write, dac_rgb[3];
static uint8_t crtc_index;

void video_set_mode(int mode)
{
    (void)mode;
    memset(gc_regs, 0, sizeof(gc_regs));
    memset(seq_regs, 0, sizeof(seq_regs));
}

uint16_t vga_port_in(uint16_t port)
{
    switch (port) {
        case 0x3c5: return seq_regs[seq_index & 7];
        case 0x3cf: return gc_regs[gc_index & 0x0f];
        case 0x3c9: return 0;
        default:    return 0;
    }
}

void vga_port_out(uint16_t port, uint16_t val)
{
    switch (port) {
        case 0x3c4: seq_index = (uint8_t)val; break;
        case 0x3c5: seq_regs[seq_index & 7] = (uint8_t)val; break;
        case 0x3ce: gc_index = (uint8_t)val; break;
        case 0x3cf: gc_regs[gc_index & 0x0f] = (uint8_t)val; break;
        case 0x3c8: dac_index = (uint8_t)val; dac_write = 0; break;
        case 0x3c9:
            dac_rgb[dac_write++] = (uint8_t)val;
            if (dac_write == 3) {
                g_palette[dac_index][0] = (uint8_t)((dac_rgb[0] & 0x3F) << 2);
                g_palette[dac_index][1] = (uint8_t)((dac_rgb[1] & 0x3F) << 2);
                g_palette[dac_index][2] = (uint8_t)((dac_rgb[2] & 0x3F) << 2);
                dac_index++;
                dac_write = 0;
            }
            break;
        default: break;
    }
}

void video_blit(void) { plat_present(); }

/* ------------------------------------------------------------------ */
/* Renderer entry points.  The full rasteriser is added incrementally;  */
/* for now these keep the state machine coherent.                       */
/* ------------------------------------------------------------------ */

void FUN_1000_3a23(void) {}
void FUN_1000_3c7e(void) {}
void FUN_1000_3c95(uintptr_t a, int _b, int _c, int _d, int _e)
{
    int16_t b = (int16_t)_b;
    int16_t c = (int16_t)_c;
    int16_t d = (int16_t)_d;
    int16_t e = (int16_t)_e; (void)a; (void)b; (void)c; (void)d; (void)e; }
void FUN_1000_3cfc(uintptr_t a, uint16_t b) { (void)a; (void)b; }
void FUN_1000_3d82(uintptr_t a, int _b, int _c, int _d)
{
    int16_t b = (int16_t)_b;
    uint16_t c = (uint16_t)_c;
    uint16_t d = (uint16_t)_d; (void)a; (void)b; (void)c; (void)d; }
void FUN_1000_3df3(uintptr_t a, uint8_t b, int16_t c) { (void)a; (void)b; (void)c; }
uint32_t FUN_1000_3e30(uint16_t a, uint8_t b) { (void)a; (void)b; return 0; }
void FUN_1000_3e6e(uintptr_t a, uintptr_t b, int _c, int _d)
{
    int16_t c = (int16_t)_c;
    int16_t d = (int16_t)_d; (void)a; (void)b; (void)c; (void)d; }

/* 1000:3c36  draw an 8x8 glyph from the font at [0x3192]:[0x3190] */
void FUN_1000_3c36(int x, int y, int ch, int color)
{
    const uint8_t *font = g_mem + ((uint32_t)*(uint16_t *)(g_ds + 0x3192) << 4) +
                          (uint16_t)(*(uint16_t *)(g_ds + 0x3190) + (uint16_t)(ch << 3));
    uint8_t *vga = g_mem + VGA_BASE;
    uint16_t di = (uint16_t)((uint16_t)y * 0x140 + (uint16_t)x);
    int r, b;
    for (r = 0; r < 8; r++) {
        uint8_t bits = font[r];
        for (b = 0; b < 8; b++, di++)
            if (bits & (0x80 >> b)) vga[di] = (uint8_t)color;
        di = (uint16_t)(di + 0x138);
    }
}
