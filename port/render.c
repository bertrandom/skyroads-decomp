/* Road / ship renderer, ported from the hand written assembly at
 * 1000:2cb2..1000:3aaf (VGA mode 13h path only) and the per-frame driver
 * at 1000:0be3.
 *
 * Data layout (all in the data segment unless noted):
 *   0x1638       road: 7 cells (16-bit) per row
 *   0xe82[8]     segments of the 8 TREKDAT perspective tables, one per
 *                1/8th of a row of forward movement
 *   0x322        shape colour -> VGA colour (left, right, ega, ega)
 *   0xb77[8]     road cell type -> height class (1 floor,2 tunnel,3 half,4 full)
 *   0xe92/0x114a ship / shadow visibility masks (29x24, 29x9)
 *   0x124f       previous frame's copy of the masks
 *   0x65e        5 shadow sprites (29x9, column major)
 *   0x44a        per screen-row clip table used for the ship mask
 *
 * A TREKDAT table starts with 13 rows x 4 cells x 6 shape pointers.  A
 * shape is: colour byte, 16-bit start offset, then (x, length, 0) span
 * triples, terminated by 0xff.  Spans are drawn one screen line apart. */
#include "compat.h"
#include "protos.h"

#define DS16(off) (*(volatile uint16_t *)(g_ds + (uint16_t)(off)))
#define DS8(off)  (*(volatile uint8_t  *)(g_ds + (uint16_t)(off)))
#define SEG(s)    (g_mem + ((uint32_t)(uint16_t)(s) << 4))

/* renderer state variables at DS:0xe34.. */
#define R_X     DS16(0xe34)   /* ship x                      */
#define R_POS   DS16(0xe36)   /* road position (1/8 rows)    */
#define R_Y     DS16(0xe38)   /* ship height                 */
#define R_SPRO  DS16(0xe3a)   /* ship sprite offset          */
#define R_SPRS  DS16(0xe3c)   /* ship sprite segment         */
#define R_FULL  DS16(0xe3e)   /* force full redraw           */
#define R_SHD   DS16(0xe40)   /* shadow distance             */
#define R_DST   DS16(0xe42)   /* back buffer segment         */
#define R_ROW   DS16(0xe50)
#define R_CELL  DS16(0xe52)
#define R_SIDE  DS16(0xe54)
#define R_PASS  DS16(0xe56)
#define R_SRC   DS16(0xe72)
#define R_TGT   DS16(0xe74)
#define R_OPOS  DS16(0xe76)

static uint8_t *T;          /* current TREKDAT segment (DS in the original) */
static uint8_t *ES;         /* destination for shape drawing               */

/* Per-pixel depth of the road surfaces of the last frame, used to hide
 * ghosts (ghost.c) behind blocks and tunnels: DEPTH_NONE (sky), DEPTH_FLOOR
 * (floor tiles: depth follows from the screen line) or (rows ahead of the
 * ship + 4) * 16 for blocks (middle of their row) and tunnels (front of
 * their row, so a ghost inside the tunnel is under its roof). */
static uint8_t s_depth[64000];
static uint8_t s_shape_depth = DEPTH_NONE;
static uint8_t s_tunnel_depth = DEPTH_NONE;
#define DEPTH_PUT(d) do { uint32_t p_ = 0x2800u + (uint16_t)(d); \
                          if (p_ < sizeof s_depth) s_depth[p_] = s_shape_depth; } while (0)
static uint16_t si_, di_, bp_;
static int right_side;      /* e40 = left (3153) / right (3190) drawer     */

static inline uint16_t TW(const uint8_t *t, uint16_t off)
{
    return (uint16_t)(t[off] | (t[(uint16_t)(off + 1)] << 8));
}

/* 1000:3137 / 1000:3174  draw a span shape (left half / mirrored right) */
static void draw_shape(void)
{
    uint8_t c = T[si_++];
    uint16_t d;
    if (!right_side) {
        uint8_t col = DS8(0x322 + c * 4);
        d = TW(T, si_); si_ += 2;
        for (;;) {
            uint8_t x = T[si_++], len;
            uint16_t line = d;
            if (x == 0xff) break;
            d = (uint16_t)(d - x);
            len = T[si_++]; si_++;
            while (len--) { DEPTH_PUT(d); ES[d++] = col; }
            d = (uint16_t)(line + 0x140);
        }
    } else {
        uint8_t col = DS8(0x323 + c * 4);
        d = (uint16_t)(TW(T, si_) - 1); si_ += 2;
        for (;;) {
            uint8_t x = T[si_++], len;
            uint16_t line = d;
            if (x == 0xff) break;
            d = (uint16_t)(d + x);
            len = T[si_++]; si_++;
            while (len--) { DEPTH_PUT(d); ES[d--] = col; }
            d = (uint16_t)(line + 0x140);
        }
    }
}

/* 1000:31b5  skip a shape */
static void skip_shape(void)
{
    do { si_ += 3; } while (T[si_] != 0xff);
    si_++;
}

#define B(k)   DS8(bp_ + (k))
#define SIDEOFF ((uint16_t)(2 - R_SIDE * 4))
#define TOPCOL() ((B(0) >> 4) ? (B(0) >> 4) : 0x3d)

/* cell handlers (table at DS:0xb7f) */
static void cell_floor_shapes(void);
static void cell_floor(void)
{
    uint8_t solid = s_shape_depth;
    s_shape_depth = DEPTH_FLOOR;
    cell_floor_shapes();
    s_shape_depth = solid;
}

static void cell_floor_shapes(void)              /* 1000:2e50 */
{
    uint8_t c = B(0) & 0xf;
    if (!c) return;
    si_ = TW(T, di_);
    T[si_] = c; draw_shape();
    if (!(DS8(bp_ + SIDEOFF) & 0xf)) { T[si_] = (uint8_t)(c + 0x1e); draw_shape(); }
    else skip_shape();
    if (B(-0xe) & 0xf) return;
    T[si_] = (uint8_t)(c + 0xf); draw_shape();
}

static void cell_half(void)                      /* 1000:2e9f */
{
    cell_floor();
    if (B(-0xd) < 2) { si_ = TW(T, di_ + 6); draw_shape(); }
    si_ = TW(T, di_ + 4);
    T[si_] = TOPCOL(); draw_shape();
    if (DS8(bp_ + SIDEOFF + 1) < 2) draw_shape();
}

static void cell_half_tunnel(void)               /* 1000:2ee1 */
{
    cell_floor();
    if (B(-0xd) < 2) { si_ = TW(T, di_ + 2); T[si_] = 0x41; draw_shape(); }
    si_ = TW(T, di_ + 4);
    T[si_] = TOPCOL(); draw_shape();
    if (DS8(bp_ + SIDEOFF + 1) < 2) draw_shape();
    if (B(-0xd) < 2) { si_ = TW(T, di_ + 6); skip_shape(); draw_shape(); draw_shape(); }
}

static void cell_full(void)                      /* 1000:2f3c */
{
    cell_floor();
    if (B(-0xd) < 2) { si_ = TW(T, di_ + 6); draw_shape(); }
    si_ = TW(T, di_ + 4);
    skip_shape();
    if (DS8(bp_ + SIDEOFF + 1) < 2) draw_shape();
    si_ = TW(T, di_ + 0xa);
    T[si_] = TOPCOL(); draw_shape();
    if (DS8(bp_ + SIDEOFF + 1) < 4) draw_shape(); else skip_shape();
    if (B(-0xd) < 4) draw_shape();
}

static void cell_full_tunnel(void)               /* 1000:2fb0 */
{
    cell_floor();
    if (B(-0xd) < 2) { si_ = TW(T, di_ + 2); T[si_] = 0x41; draw_shape(); }
    si_ = TW(T, di_ + 4);
    skip_shape();
    if (DS8(bp_ + SIDEOFF + 1) < 2) draw_shape();
    if (B(-0xd) < 2) { si_ = TW(T, di_ + 6); skip_shape(); draw_shape(); draw_shape(); }
    si_ = TW(T, di_ + 0xa);
    T[si_] = TOPCOL(); draw_shape();
    if (DS8(bp_ + SIDEOFF + 1) < 4) draw_shape(); else skip_shape();
    if (B(-0xd) < 4) draw_shape();
}

static void cell_tunnel(void)                    /* 1000:303d */
{
    int k;
    cell_floor();
    if (B(-0xd) < 1) { si_ = TW(T, di_ + 2); T[si_] = 0x43; draw_shape(); }
    si_ = TW(T, di_ + 8);
    for (k = 0; k < 6; k++) draw_shape();
    if (B(-0xd) < 1) { draw_shape(); draw_shape(); }
}

static void cell_dispatch(void)
{
    uint8_t block = s_shape_depth;
    switch (B(1) & 0xf) {
        case 0: cell_floor(); break;
        case 1: s_shape_depth = s_tunnel_depth; cell_tunnel(); break;
        case 2: cell_half(); break;
        case 3: s_shape_depth = s_tunnel_depth; cell_half_tunnel(); break;
        case 4: cell_full(); break;
        case 5: s_shape_depth = s_tunnel_depth; cell_full_tunnel(); break;
        default: break;
    }
    s_shape_depth = block;
}

static uint8_t depth_code(float rows_ahead)
{
    float c = (rows_ahead + 4.0f) * 16.0f;
    return (uint8_t)(c < 0 ? 0 : c > DEPTH_MAX ? DEPTH_MAX : c);
}

/* ------------------------------------------------------------------ */
/* ship                                                                */
/* ------------------------------------------------------------------ */

/* 1000:32a5  compute the ship / shadow visibility masks */
static void ship_mask(void)
{
    uint16_t di = 0xe92, bx = R_Y, si = (uint16_t)((0x9d - R_Y) * 2);
    int dx;
    memset(g_ds + 0xe92, 0, 0x3bc);
    for (dx = 0x21; dx; dx--) {
        if (!(bx > 0x9d) && !(bx < 0x14)) {
            uint16_t lo = 0x6e, hi = 0x1ae, w = DS16(si + 0x44a), b, cnt, b2;
            if (w != 0) {
                uint16_t ax = (uint16_t)(0x10e - w);
                if ((int16_t)R_X >= (int16_t)ax) lo = (uint16_t)(0x10e + w);
                if ((int16_t)R_X < (int16_t)ax) hi = ax;
            }
            b = (uint16_t)(lo - R_X);
            if ((int16_t)b < 0) b = 0;
            if (b < 0x1d) {
                uint16_t d = (uint16_t)(di + b);
                cnt = (uint16_t)(0x1d - b);
                b2 = (uint16_t)(R_X + 0x1d - hi);
                if ((int16_t)b2 < 0) b2 = 0;
                if (b2 < cnt) memset(g_ds + d, 1, (size_t)(cnt - b2));
            }
        }
        di += 0x1d; bx--; si += 2;
        if (dx == 0xa) {
            uint16_t ax = (uint16_t)(R_SHD - 8);
            bx = (uint16_t)(bx - ax);
            si = (uint16_t)(si + ax * 2);
        }
    }
}

/* 1000:33e1  shadow: darken floor pixels under the ship */
static void ship_shadow(uint8_t *es)
{
    uint16_t n = (uint16_t)(R_SHD / 5), si, di, bx;
    int col, row;
    if (n >= 5) return;
    si = (uint16_t)(0x65e + n * 0x105);
    di = (uint16_t)((uint16_t)(0x9d - R_Y + 0x10 + R_SHD) * 0x140 + R_X - 0x6e);
    DS16(0xe7c) = di;
    bx = 0;
    for (col = 0; col < 0x1d; col++) {
        for (row = 0; row < 9; row++) {
            if (DS8(bx + si) != 0 && DS8(bx + 0x114a) != 0) {
                uint8_t al;
                DS8(bx + 0x114a) = 2;
                al = es[di];
                if (al == 0x3d) al = 0x40;
                if (al != 0 && al < 0x10) al = (uint8_t)(al + 0x2d);
                es[di] = al;
            }
            di = (uint16_t)(di + 0x140); bx += 0x1d;
        }
        di = (uint16_t)(di - 0xb3f); bx = (uint16_t)(bx - 0x104);
    }
}

/* 1000:323f  draw the ship sprite (column major, 29x24) */
static void draw_ship(void)
{
    uint8_t *es = SEG(R_DST);
    const uint8_t *spr = SEG(R_SPRS) + R_SPRO;
    uint16_t di, bx = 0;
    int col, row;
    ship_mask();
    di = (uint16_t)((uint16_t)(0x9d - R_Y) * 0x140 + R_X - 0x6e);
    DS16(0xe78) = di;
    for (col = 0; col < 0x1d; col++) {
        for (row = 0; row < 0x18; row++) {
            uint8_t al = *spr++;
            if (al != 0 && DS8(bx + 0xe92) != 0) {
                DS8(bx + 0xe92) = 2;
                es[di] = al;
            }
            di = (uint16_t)(di + 0x140); bx += 0x1d;
        }
        di = (uint16_t)(di - 0x1dff); bx = (uint16_t)(bx - 0x2b7);
    }
    ship_shadow(es);
}

/* ------------------------------------------------------------------ */
/* dirty-region copying                                                */
/* ------------------------------------------------------------------ */

/* 1000:3a06  copy masked 29-wide rectangle */
static void copy_masked(uint16_t si, uint16_t bx, int rows)
{
    const uint8_t *src = SEG(R_SRC);
    uint8_t *dst = SEG(R_TGT);
    while (rows--) {
        int k;
        for (k = 0; k < 0x1d; k++, si++, bx++)
            if (DS8(bx) == 2) dst[si] = src[si];
        si = (uint16_t)(si + 0x123);
    }
}

/* 1000:39b8  refresh the old and new ship rectangles */
static void copy_ship_areas(void)
{
    copy_masked(DS16(0xe7a), 0x124f, 0x18);
    copy_masked(DS16(0xe7e), 0x1507, 9);
    if (R_TGT == 0xa000) {
        copy_masked(DS16(0xe78), 0xe92, 0x18);
        copy_masked(DS16(0xe7c), 0x114a, 9);
    }
}

static uint16_t skip_n(const uint8_t *t, uint16_t bx, int n)
{
    while (n-- > 0) {
        do { bx += 3; } while (t[bx] != 0xff);
        bx++;
    }
    return bx;
}

/* 1000:38a3  copy the spans covered by shape `code` between buffers */
static void copy_shape_area(uint16_t code)
{
    const uint8_t *tp = SEG(DS16(0xe6e)), *tn = SEG(DS16(0xe6c));
    const uint8_t *src = SEG(R_SRC);
    uint8_t *dst = SEG(R_TGT);
    uint16_t idx, bx, si_old, bp;
    int n = code & 0xff;
    idx = (uint16_t)(((code & 0x7fff) >> 7) + ((11 - R_ROW) * 4 + 4 - R_CELL) * 12);
    bx = skip_n(tp, TW(tp, (uint16_t)(idx + DS16(0xe70))), n);
    si_old = TW(tp, bx + 1);
    bx = skip_n(tn, TW(tn, idx), n);
    bp = TW(tn, bx + 1);
    bx += 3;
    if (!(code & 0x8000)) {
        for (;;) {
            if (tn[bx] == 0xff) return;
            if (bp >= si_old) break;
            bx += 3; bp = (uint16_t)(bp + 0x140);
        }
    }
    bp = (uint16_t)(bp + 0x2800);
    if (R_SIDE == 0) {
        for (;;) {
            uint8_t x = tn[bx];
            uint16_t s, cx;
            if (x == 0xff) break;
            s = (uint16_t)(bp - x);
            cx = tn[bx + 1];
            if (s & 1) cx++;
            s &= 0xfffe;
            cx = (uint16_t)((cx >> 1) + (cx & 1));
            memmove(dst + s, src + s, (size_t)cx * 2);
            bp = (uint16_t)(bp + 0x140); bx += 3;
        }
    } else {
        bp--;
        for (;;) {
            uint8_t x = tn[bx];
            uint16_t s, cx, start;
            if (x == 0xff) break;
            s = (uint16_t)(bp + x);
            cx = tn[bx + 1];
            if (!(s & 1)) cx++;
            s &= 0xfffe;
            cx = (uint16_t)((cx >> 1) + (cx & 1));
            start = (uint16_t)(s - (cx - 1) * 2);
            memmove(dst + start, src + start, (size_t)cx * 2);
            bp = (uint16_t)(bp + 0x140); bx += 3;
        }
    }
}

#define V(o) DS16(o)
/* 1000:3633  restore background for cells that will change */
static void restore_cell(void)
{
    uint16_t e4e = V(0xe5a), e50 = V(0xe5c), e52 = V(0xe5e);
    if (V(0xe62) == 0 && V(0xe64) != 0) {
        if (e50 == 1) copy_shape_area(0);
        if (V(0xe66) == 0) copy_shape_area(1);
    }
    if (e4e < 3) {
        if (e50 == 3) copy_shape_area(0x200);
        if (e50 >= 3 && e52 < 3) copy_shape_area(0x201);
    }
    if (e4e == 1 && e50 == 2) {
        int k;
        for (k = 0; k < 6; k++) copy_shape_area((uint16_t)(0x400 + k));
    }
    if (e4e < 4 && e50 == 4) {
        copy_shape_area(0x500);
        if (e52 < 4) copy_shape_area(0x501);
    }
}

/* 1000:36d7  copy changed cell areas from the back buffer to the screen */
static void present_cell(void)
{
    uint16_t e4e = V(0xe5a), e50 = V(0xe5c), e52 = V(0xe5e), e54 = V(0xe60);
    uint16_t e56 = V(0xe62), e58 = V(0xe64), e5a = V(0xe66);
    uint16_t e5c = V(0xe68), e5e = V(0xe6a);
    if (e4e == 1 && e58 != e56 && e50 == 1) copy_shape_area(0);
    if (e56 != 0 && e58 == 0 && (R_CELL <= 2 || e54 == 1)) copy_shape_area(0x8002);
    if (e5a == 0 && e58 != e56 && e54 == 1) copy_shape_area(1);
    if ((e4e == 2 || e4e == 3) && (e50 != e4e || e5e != e5c)) copy_shape_area(0x200);
    if (e4e >= 2 && e50 < 3 && !(e4e == 2 && e50 == 2)) copy_shape_area(0x8300);
    if ((e4e == 2 && e50 != 2) || (e4e >= 3 && e50 < 3 && e52 < 3)) copy_shape_area(0x201);
    if (e4e == 4 && (e50 != 4 || e5e != e5c)) copy_shape_area(0x500);
    if (e4e == 4 && e50 < 4) copy_shape_area(0x8502);
    if (e4e == 4 && e50 < 4 && e52 < 4) copy_shape_area(0x501);
    if (e50 > e4e) {
        if (e4e <= 2) {
            if (e50 == 4) {
                copy_shape_area(0x500);
                if (e52 != 4 && e54 != 4) copy_shape_area(0x501);
                if (e52 < 3 && e54 < 3) copy_shape_area(0x201);
            } else if (e50 == 2) {
                int k;
                for (k = 0; k < 6; k++) copy_shape_area((uint16_t)(0x400 + k));
            } else {
                copy_shape_area(0x200);
                if (e52 < 3 && e54 < 3) copy_shape_area(0x201);
            }
        } else {
            copy_shape_area(0x500);
            if (e52 != 4 && e54 != 4) copy_shape_area(0x501);
        }
    }
}

/* 1000:3492  background restore (phase 0) / screen update (phase 1) */
static void update_regions(int phase)
{
    uint16_t d;
    if (DS16(0x36) == 0) return;
    R_SRC = DS16(0x517e);
    R_TGT = R_DST;
    if (phase) { R_SRC = R_DST; R_TGT = 0xa000; }
    if (R_FULL == 0) {
        d = (uint16_t)(R_POS - R_OPOS);
        if (d == 0) { copy_ship_areas(); return; }
        if (d < 8) {
            uint16_t e4c;
            DS16(0xe70) = (uint16_t)(((R_POS >> 3) == (R_OPOS >> 3)) ? 0x30 : 0);
            DS16(0xe6e) = DS16(0xe82 + (R_OPOS & 7) * 2);
            DS16(0xe6c) = DS16(0xe82 + (R_POS & 7) * 2);
            e4c = (uint16_t)(0x1638 + (R_POS >> 3) * 14 + 0x62);
            for (R_ROW = 11; R_ROW != 1; R_ROW--, e4c -= 14) {
                for (R_CELL = 1; R_CELL <= 4; R_CELL++) {
                    R_SIDE = 0;
                    do {
                        uint16_t ax = (uint16_t)(4 - R_CELL), bx;
                        uint16_t so = (uint16_t)(2 - R_SIDE * 4);
                        if (R_SIDE == 1) ax = (uint16_t)(6 - ax);
                        bx = (uint16_t)(e4c + ax * 2);
                        V(0xe62) = DS8(bx) & 0xf;
                        V(0xe68) = DS8(bx) >> 4;
                        V(0xe5a) = DS8(0xb77 + (DS8(bx + 1) & 7));
                        V(0xe64) = DS8(bx - 0xe) & 0xf;
                        V(0xe6a) = DS8(bx - 0xe) >> 4;
                        V(0xe5c) = DS8(0xb77 + (DS8(bx - 0xd) & 7));
                        V(0xe66) = DS8(bx + so) & 0xf;
                        V(0xe5e) = DS8(0xb77 + (DS8(bx + so + 1) & 7));
                        V(0xe60) = DS8(0xb77 + (DS8(bx + so - 0xd) & 7));
                        if (phase) present_cell(); else restore_cell();
                        R_SIDE ^= 1;
                    } while (R_SIDE != 0);
                }
            }
            copy_ship_areas();
            return;
        }
    }
    {
        uint16_t off = R_FULL ? 0 : 0x2800;
        uint32_t len = R_FULL ? 0x5640u * 2 : 0x4240u * 2;
        memmove(SEG(R_TGT) + off, SEG(R_SRC) + off, len);
    }
    copy_ship_areas();
}

/* 1000:2d03  render road + ship into the back buffer and update screen */
void FUN_1000_2d03(int x, int pos, int y, int spr_off, int spr_seg,
                   int full, int shadow, int dst)
{
    uint16_t saved_di = 0;
    R_X = (uint16_t)x; R_POS = (uint16_t)pos; R_Y = (uint16_t)y;
    R_SPRO = (uint16_t)spr_off; R_SPRS = (uint16_t)spr_seg;
    R_FULL = (uint16_t)full; R_SHD = (uint16_t)shadow; R_DST = (uint16_t)dst;

    update_regions(0);
    memset(s_depth, DEPTH_NONE, sizeof s_depth);

    ES = SEG((uint16_t)(R_DST + 0x280));
    bp_ = (uint16_t)(0x1638 + (R_POS >> 3) * 14 + 0x62);
    T = SEG(DS16(0xe82 + (R_POS & 7) * 2));
    di_ = 0;
    R_PASS = 0;
    R_ROW = 11;
    for (;;) {
        R_SIDE = 0;
        right_side = 0;
        if (R_ROW == 4) { saved_di = di_; di_ = R_PASS ? 0x240 : 0x210; }
        {   /* front and middle of this row (or of the half row around the
             * ship), in rows ahead of the ship */
            float frac = (float)(R_POS & 7) / 8.0f, front, back;
            if (R_ROW != 4) { front = (float)R_ROW - 4.0f - frac; back = front + 1.0f; }
            else if (R_PASS) { front = -frac; back = 0.0f; }
            else { front = 0.0f; back = 1.0f - frac; }
            s_shape_depth = depth_code((front + back) / 2.0f);
            /* ghost.c hides a ghost behind surfaces > 0.3 rows nearer */
            s_tunnel_depth = depth_code(front - 0.3f);
        }
        do {
            for (R_CELL = 4; R_CELL; R_CELL--) {
                cell_dispatch();
                di_ += 0xc;
                bp_ += 2;
                if (R_SIDE) bp_ -= 4;
            }
            di_ -= 0x30;
            bp_ += 4;
            right_side = 1;
            R_SIDE++;
        } while (R_SIDE < 2);
        if (R_ROW == 4) {
            di_ = saved_di;
            R_PASS++;
            if (R_PASS < 2) { bp_ -= 8; draw_ship(); continue; }
        }
        di_ += 0x30;
        bp_ -= 0x16;
        if (--R_ROW == 0) break;
    }

    update_regions(1);
    s_shape_depth = DEPTH_NONE;
    R_OPOS = R_POS;
    DS16(0xe7a) = DS16(0xe78);
    DS16(0xe7e) = DS16(0xe7c);
    memmove(g_ds + 0x124f, g_ds + 0xe92, 0x1de * 2);
}

/* 1000:3a7a  expand the TREKDAT tables in place (VGA format) */
static void prepare_trekdat(void)
{
    int k;
    for (k = 0; k < 8; k++) {
        uint8_t *t = SEG(DS16(0xe82 + k * 2));
        uint16_t si = TW(t, 0), di = 0;
        int n, shapes;
        if (DS16(0xe82 + k * 2) == 0) continue;
        for (n = 0; n < 0x138 * 2; n++) t[di++] = t[si++];
        for (shapes = 0; shapes < 0x410; shapes++) {
            t[di++] = t[si++];              /* colour */
            t[di++] = t[si++];              /* start offset */
            t[di++] = t[si++];
            for (;;) {
                uint8_t al = t[si++];
                t[di++] = al;
                if (al == 0xff) break;
                t[di++] = t[si++];
                t[di++] = 0;
            }
        }
    }
}

/* 1000:2cb2  renderer initialisation */
uint16_t FUN_1000_2cb2(void)
{
    prepare_trekdat();
    DS16(0xe44) = 0x348b;
    DS16(0xe46) = 0x3137;
    DS16(0xe48) = 0x3174;
    DS16(0xe4a) = 0x323f;
    return 0;
}

/* ------------------------------------------------------------------ */
/* 1000:0be3  per-frame: draw road and ship from the game state        */
/* ------------------------------------------------------------------ */

void FUN_1000_0be3(int param_1)
{
    int16_t v6, si, v8, va;
    uint16_t p1, p2, p3, p7, p8;
    {   /* debug: SKY_WARP=n jumps to n rows before the end of the road */
        static int warped;
        const char *w = getenv("SKY_WARP");
        if (w && !warped && DS16(0x41ce) > (uint16_t)atoi(w) && DS16(0x962a) > 2) {
            DS16(0x962a) = (uint16_t)(DS16(0x41ce) - atoi(w));
            warped = 1;
        }
    }
    v6 = FUN_1000_0533(DS16(0x9628), DS16(0x962a), DS16(0xaf2c), DS16(0xaf3c));
    if (getenv("SKY_DEBUG") && DS16(0x962a) + 2 >= DS16(0x41ce))
        fprintf(stderr, "[end? pos=%04x:%04x len=%u x=%04x y=%04x tunnel=%d 456e=%u]\n",
                DS16(0x962a), DS16(0x9628), DS16(0x41ce), DS16(0xaf2c), DS16(0xaf3c), v6, DS16(0x457c));
    if (DS16(0x4578) != 0) {
        si = (int16_t)(DS16(0x4578) / 3);
        if ((uint16_t)si >= 0xe) si = -1;
    } else {
        int16_t c = (DS16(0x457c) == 4) ? 0 : (int16_t)DS16(0xea + ((DS16(0x160c) / 2) % 4) * 2);
        int16_t e = v6 ? 0 : FUN_1000_0afa(DS16(0x9342), DS16(0xaf3c));
        si = (int16_t)((FUN_1000_0b34(DS16(0xaf2c)) * 3 + e) * 3 + 0xe + c);
    }
    ghost_frame(si);
    sound_poll();
    v8 = FUN_1000_0b71(DS16(0x9628), DS16(0x962a), (uint16_t)(DS16(0xaf2c) - 0x380), v6);
    va = FUN_1000_0b71(DS16(0x9628), DS16(0x962a), (uint16_t)(DS16(0xaf2c) + 0x380), v6);
    if (DS16(0xe28) == DS16(0x9628) && DS16(0xe2a) == DS16(0x962a) &&
        DS16(0xe2c) == DS16(0xaf2c) && DS16(0xe2e) == DS16(0xaf3c) &&
        DS16(0xe30) == (uint16_t)si && DS16(0xe32) == DS16(0x9340)) {
        ghost_publish(NULL);                /* frame unchanged, ghosts moved */
        return;
    }
    DS16(0xe28) = DS16(0x9628);
    DS16(0xe2a) = DS16(0x962a);
    DS16(0xe2c) = DS16(0xaf2c);
    DS16(0xe2e) = (uint16_t)(param_1 ? DS16(0xaf3c) - 0x80 : DS16(0xaf3c));
    DS16(0xe30) = (uint16_t)si;
    DS16(0xe32) = DS16(0x9340);

    p8 = DS16(0x36) ? DS16(0x5486) : (uint16_t)(0xa000 + ((DS16(0x9340) == 0) << 9));
    if (DS16(0x4578) != 0) p7 = 0x7fff;
    else {
        uint16_t m = ((uint16_t)v8 >= (uint16_t)va) ? (uint16_t)v8 : (uint16_t)va;
        p7 = (uint16_t)((uint16_t)(DS16(0xaf3c) - m) / 0x80);
    }
    p3 = (si == -1) ? 0 : (uint16_t)(DS16(0xe2e) / 0x80);
    p2 = (uint16_t)FUN_1000_5d4e(DS16(0x9628), DS16(0x962a), 0x2000, 0);
    p1 = (uint16_t)(DS16(0xaf2c) / 0x80 + DS16(0x38 + FUN_1000_0b34(DS16(0xaf2c)) * 2));
    FUN_1000_2d03(p1, p2, p3, (uint16_t)(DS16(0xaf44) + si * 0x2d0), DS16(0xaf46),
                  0, p7, p8);
    ghost_publish(s_depth);
    DS16(0x9340) ^= 1;
}
