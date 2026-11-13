/* Game routines ported by hand from the disassembly because the Ghidra
 * output lost segment registers, register arguments or self-modifying code.
 * Each function lists the original address. */
#include "compat.h"
#include "protos.h"
#include <SDL.h>

#define DS16(off) (*(volatile uint16_t *)(g_ds + (off)))
#define DS8(off)  (*(volatile uint8_t  *)(g_ds + (off)))
#define SEG(s)    (g_mem + ((uint32_t)(uint16_t)(s) << 4))

void hw_timer_isr_install(int on);
void hw_kbd_isr_install(int on);
void hw_wait_vsync(void);
void speaker_set_divisor(uint16_t div);
void speaker_gate(int on);
void sb_stop(void);
void opl_silence(void);


/* 1000:0046  shut down and exit */
void FUN_1000_0046(void)
{
    FUN_1000_601d(3);
    FUN_1000_3b6b();
    FUN_1000_58a5();
    FUN_1000_5bc0();
    FUN_1000_6001(0);
}

/* 1000:0eeb  wait until the timer tick counter changes */
void FUN_1000_0eeb(void)
{
    uint16_t t = DS16(0x1600);
    while (DS16(0x1600) == t) SDL_Delay(1);
}

/* 1000:0f62  expand a 0/1/other mask into the scratch buffer [0xaf2a]:0 */
void FUN_1000_0f62(int _src_off, int _src_seg, int _n, int _col1, int _col2)
{
    uint16_t src_off = (uint16_t)_src_off;
    uint16_t src_seg = (uint16_t)_src_seg;
    uint16_t n = (uint16_t)_n;
    uint16_t col1 = (uint16_t)_col1;
    uint16_t col2 = (uint16_t)_col2;
    uint8_t *dst = SEG(DS16(0xaf2a));
    const uint8_t *src = SEG(src_seg) + src_off;
    while (n--) {
        uint8_t v = *src++;
        *dst++ = (uint8_t)(v == 0 ? 0 : v == 1 ? col1 : col2);
    }
}

/* 1000:41a0  blit one row with background merge.
 *   copy `lead` bytes bg->dst (same offset), then for the middle
 *   [0x9612]-lead-trail sprite bytes: values < [0x9614] are transparent,
 *   values < [0xaf3a] show the background, others are drawn; finally copy
 *   `trail` bytes bg->dst. */
void FUN_1000_41a0(int _dst_off, int _src_off, int _lead, int _trail)
{
    uint16_t dst_off = (uint16_t)_dst_off;
    uint16_t src_off = (uint16_t)_src_off;
    uint16_t lead = (uint16_t)_lead;
    uint16_t trail = (uint16_t)_trail;
    uint8_t thr = DS8(0x9614);
    uint8_t hi  = DS8(0xaf3a);
    uint8_t *bg  = SEG(DS16(0x4512));
    uint8_t *spr = SEG(DS16(0x4514));
    uint8_t *dst = SEG(DS16(0x961c));
    uint16_t di = dst_off, si = src_off, cx;
    for (cx = lead; cx; cx--, di++) dst[di] = bg[di];
    cx = (uint16_t)(DS16(0x9612) - lead - trail);
    while (cx--) {
        uint8_t al = spr[si++];
        if (al < thr) { di++; continue; }
        if (al < hi) al = bg[di];
        dst[di++] = al;
    }
    for (cx = trail; cx; cx--, di++) dst[di] = bg[di];
}

/* 1000:4201  blit an image descriptor {seg, pos, rows, width} */
void FUN_1000_4201(uintptr_t pdesc)
{
    uint16_t *desc = (uint16_t *)near_ptr(pdesc);
    uint16_t row, pos, src;
    DS16(0x4514) = desc[0];
    DS16(0x9612) = desc[3];
    if ((DS16(0x961c) & 0xa000) == 0xa000 && DS16(0x3c) == 0) {
        FUN_1000_3d18(desc[1], desc[2]);
        return;
    }
    pos = desc[1];
    src = 0;
    for (row = 0; row < desc[2]; row++) {
        FUN_1000_41a0(pos, src, 0, 0);
        pos = (uint16_t)(pos + 0x140);
        src = (uint16_t)(src + desc[3]);
    }
}

/* 1000:0f8c  draw a mask image (far pointer off:seg) at its stored position */
void FUN_1000_0f8c(int _off, int _seg, int _lit)
{
    uint16_t off = (uint16_t)_off;
    uint16_t seg = (uint16_t)_seg;
    uint16_t lit = (uint16_t)_lit;
    uint16_t desc[4];
    uint8_t *img = SEG(seg) + off;
    uint16_t c1, c2, w, h;
    if (DS16(0x3c) != 0) { c1 = lit ? 0x5e : 0x5c; c2 = lit ? 0x5f : 0x5d; }
    else                 { c1 = 0;                 c2 = lit ? 5 : 8; }
    w = img[2];
    h = img[3];
    desc[0] = DS16(0xaf2a);
    desc[1] = (uint16_t)(img[0] | (img[1] << 8));
    desc[2] = h;
    desc[3] = w;
    FUN_1000_0f62((uint16_t)(off + 4), seg, (uint16_t)(w * h), c1, c2);
    if (DS16(0x3c) == 0) FUN_1000_3c9a();
    FUN_1000_417e(0, 0xa000, 0, 1);
    FUN_1000_4201((uintptr_t)desc);
    if (DS16(0x3c) == 0) {
        FUN_1000_417e(0, 0xa200, 0, 1);
        FUN_1000_4201((uintptr_t)desc);
    }
}

/* 1000:1073  draw a w*h mask (DS offset) at x,y */
void FUN_1000_1073(int _x, int _y, int _w, int _h, int _src)
{
    int16_t x = (int16_t)_x;
    int16_t y = (int16_t)_y;
    uint16_t w = (uint16_t)_w;
    uint16_t h = (uint16_t)_h;
    uint16_t src = (uint16_t)_src;
    uint16_t desc[4];
    uint16_t c1, c2;
    if (DS16(0x3c) != 0) { c1 = 0x61; c2 = 0x62; }
    else                 { c1 = c2 = 0xe; }
    FUN_1000_0f62(src, 0x1676, (uint16_t)(w * h), c1, c2);
    desc[0] = DS16(0xaf2a);
    desc[1] = (uint16_t)(y * 0x140 + x);
    desc[2] = h;
    desc[3] = w;
    if (DS16(0x3c) == 0) FUN_1000_3c9a();
    FUN_1000_417e(0, 0xa000, 0, 0);
    FUN_1000_4201((uintptr_t)desc);
    if (DS16(0x3c) == 0) {
        FUN_1000_417e(0, 0xa200, 0, 0);
        FUN_1000_4201((uintptr_t)desc);
    }
}

/* 1000:1191 / 1000:11d3  get / put pixel */
uint16_t FUN_1000_1191(int _x, int _y)
{
    int16_t x = (int16_t)_x;
    int16_t y = (int16_t)_y;
    if (DS16(0x3c) != 0) return SEG(0xa000)[(uint16_t)(y * 0x140 + x)];
    return (uint16_t)FUN_1000_3e4c(x, y);
}

void FUN_1000_11d3(int _x, int _y, int _c)
{
    int16_t x = (int16_t)_x;
    int16_t y = (int16_t)_y;
    uint16_t c = (uint16_t)_c;
    if (DS16(0x3c) != 0) { SEG(0xa000)[(uint16_t)(y * 0x140 + x)] = (uint8_t)c; return; }
    FUN_1000_3e0f(x, y, c);
}

/* 1000:2b0f  EGA latch copy of 8000 bytes from segment src to dst */
void FUN_1000_2b0f(int _dst_seg, int _src_seg)
{
    uint16_t dst_seg = (uint16_t)_dst_seg;
    uint16_t src_seg = (uint16_t)_src_seg;
    memmove(SEG(dst_seg), SEG(src_seg), 8000);
}

/* 1000:4052  add `delta` to every non-zero byte of a far buffer */
void FUN_1000_4052(int _off, int _seg, int _cnt_lo, int _cnt_hi, int _delta)
{
    uint16_t off = (uint16_t)_off;
    uint16_t seg = (uint16_t)_seg;
    uint16_t cnt_lo = (uint16_t)_cnt_lo;
    int16_t cnt_hi = (int16_t)_cnt_hi;
    uint8_t delta = (uint8_t)_delta;
    uint32_t addr = ((uint32_t)seg << 4) + off;
    uint32_t n = (uint32_t)cnt_lo + ((uint32_t)(uint16_t)cnt_hi << 16);
    if (cnt_hi < 0) n = cnt_lo;
    while (n--) {
        if (g_mem[addr]) g_mem[addr] = (uint8_t)(g_mem[addr] + delta);
        addr++;
    }
}

/* 1000:3acc  install the 180 Hz timer interrupt */
void FUN_1000_3acc(void)
{
    hw_timer_isr_install(1);
}

/* 1000:3b6b  restore the timer interrupt and silence the speaker */
void FUN_1000_3b6b(void)
{
    hw_timer_isr_install(0);
    speaker_gate(0);
}

/* 1000:3b9d  install the keyboard interrupt (clears key-down flags) */
void FUN_1000_3b9d(void)
{
    uint16_t bx = 0xbd2;
    do { DS8(bx) &= 0x7f; } while (DS8(bx++) != 0);
    hw_kbd_isr_install(1);
}

/* 1000:3c03  remove the keyboard interrupt */
void FUN_1000_3c03(void)
{
    hw_kbd_isr_install(0);
}

/* 1000:6006  wait for vertical retrace */
void FUN_1000_6006(void)
{
    hw_wait_vsync();
}

/* 1000:60ee  rewind a file */
void FUN_1000_60ee(int _handle)
{
    uint16_t handle = (uint16_t)_handle;
    FUN_1000_5ca6(handle, 0, 0, 0);
}
