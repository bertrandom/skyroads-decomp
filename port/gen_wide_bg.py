#!/usr/bin/env python3
"""Embed the widescreen margins of the painted road backdrops as wide_bg.h.

usage: gen_wide_bg.py DIR wide_bg.h [PANEL.png [MENUDIR]]
DIR holds worldN_filled.png (N = 0..9), all the same size: pictures of the
whole widescreen frame, 240 rows tall (the 320x200 screen stretched to 4:3,
rows 1.2x tall) with the original screen in the middle, (width - 320) / 2
columns from the left, and painted on either side.  Only the side margins
are kept, at the game's 200 rows: the PNG row whose middle is nearest each
game row's middle (the inverse of a nearest-neighbour stretch).  The game
shows as much of them as the window's shape leaves room for.
The frame's own outer WIDE_BG_EDGE columns are kept as painted too: some
backdrops (Blue Planet) have a dark line at the original picture's edges,
which the game covers where the backdrop shows.
Worlds without a picture are marked missing (platform.c mirrors the
backdrop instead).

PANEL.png, as wide as the backdrops and 85 rows tall, is the control panel
(screen rows 129-199, stretched the same way) painted out to the same width,
transparent where the backdrop shows: its side margins are kept too, at 71
rows, and drawn over the backdrop's.

MENUDIR holds the menu screens painted out the same way (same size):
mainmenu_nologo_filled.png (the intro and main menu's checkerboard) and
controls_filled.png (the blue backdrop of the Controls, road selection and
help screens; it blends into the original picture near its edges, so the
frame's own outer WIDE_BG_EDGE columns are kept too).  Their margins use only colours of the screens' own
palettes, so they are kept as colour numbers into a small table per
picture: platform.c finds the palette index each colour has on the screen
and draws through the live palette (fades, the intro's colour cycling).
Needs ImageMagick (`magick`).
"""
import os
import subprocess
import sys

H, ROWS = 240, 200
src, out = sys.argv[1], sys.argv[2]
panel = sys.argv[3] if len(sys.argv) > 3 else None
menu_dir = sys.argv[4] if len(sys.argv) > 4 else None
MENUS = ['mainmenu_nologo_filled.png', 'controls_filled.png']
MAX_COLS = 64
PANEL_ROWS, PANEL_H = 71, 85
paths = [os.path.join(src, 'world%d_filled.png' % n) for n in range(10)]
present = [p for p in paths if os.path.exists(p)]
if present:
    W = int(subprocess.run(['magick', 'identify', '-format', '%w', present[0]],
                           check=True, capture_output=True, text=True).stdout)
else:
    W = 320
LEFT = (W - 320) // 2
RIGHT = W - 320 - LEFT
have = []
data = bytearray()
edge = bytearray()   # the frame's own outer EDGE columns, painted
EDGE = 3
for path in paths:
    if not os.path.exists(path):
        have.append(0)
        data += bytes(ROWS * (LEFT + RIGHT) * 3)
        edge += bytes(ROWS * 2 * EDGE * 3)
        continue
    rgb = subprocess.run(['magick', path, '-depth', '8', 'rgb:-'],
                         check=True, capture_output=True).stdout
    assert len(rgb) == W * H * 3, '%s is not %dx%d' % (path, W, H)
    have.append(1)
    for y in range(ROWS):
        line = rgb[int((y + 0.5) * H / ROWS) * W * 3:][:W * 3]
        data += line[:LEFT * 3] + line[(LEFT + 320) * 3:]
        edge += line[LEFT * 3:(LEFT + EDGE) * 3] + line[(LEFT + 320 - EDGE) * 3:(LEFT + 320) * 3]
with open(out, 'w') as f:
    f.write("/* generated from %s by gen_wide_bg.py */\n" % src)
    f.write("#define WIDE_BG_LEFT %d\n#define WIDE_BG_RIGHT %d\n" % (max(LEFT, 1), max(RIGHT, 1)))
    f.write("static const unsigned char wide_bg_have[10] = { %s };\n" % ", ".join(map(str, have)))
    f.write("/* [world][row][left %d | right %d columns][rgb] */\n" % (LEFT, RIGHT))
    f.write("static const unsigned char wide_bg[10][%d][%d][3] = {\n" % (ROWS, max(LEFT + RIGHT, 2)))
    for i in range(0, len(data), 24):
        f.write(",".join(str(b) for b in data[i:i + 24]) + ",\n")
    f.write("};\n")
    f.write("/* the frame's outer columns as painted: [world][row][left %d | right %d][rgb] */\n" % (EDGE, EDGE))
    f.write("#define WIDE_BG_EDGE %d\n" % EDGE)
    f.write("static const unsigned char wide_bg_edge[10][%d][%d][3] = {\n" % (ROWS, 2 * EDGE))
    for i in range(0, len(edge), 24):
        f.write(",".join(str(b) for b in edge[i:i + 24]) + ",\n")
    f.write("};\n")
    pdata = None
    if panel and os.path.exists(panel) and W > 320:
        rgba = subprocess.run(['magick', panel, '-depth', '8', 'rgba:-'],
                              check=True, capture_output=True).stdout
        if len(rgba) == W * PANEL_H * 4:
            pdata = bytearray()
            for y in range(PANEL_ROWS):
                line = rgba[int((y + 0.5) * PANEL_H / PANEL_ROWS) * W * 4:][:W * 4]
                line = line[:LEFT * 4] + line[(LEFT + 320) * 4:]
                for k in range(0, len(line), 4):     # opaque or not
                    pdata += line[k:k + 3] + (b'\xff' if line[k + 3] >= 128 else b'\0')
        else:
            print('%s is not %dx%d: no wide control panel' % (panel, W, PANEL_H), file=sys.stderr)
    f.write("/* the control panel's margins (screen rows 129-199), rgba, a = 0 or 255 */\n")
    f.write("#define WIDE_PANEL_HAVE %d\n" % (1 if pdata else 0))
    f.write("static const unsigned char wide_panel[%d][%d][4] = {\n" % (PANEL_ROWS, max(LEFT + RIGHT, 2)))
    if not pdata:
        pdata = bytes(PANEL_ROWS * max(LEFT + RIGHT, 2) * 4)
    for i in range(0, len(pdata), 24):
        f.write(",".join(str(b) for b in pdata[i:i + 24]) + ",\n")
    f.write("};\n")
    # the menu screens' margins: colour numbers into a table per picture
    menu_have, menu_cols, menu_px, menu_edge = [], [], bytearray(), bytearray()
    for name in MENUS:
        path = os.path.join(menu_dir, name) if menu_dir else ''
        cols = []
        if path and os.path.exists(path) and W > 320:
            rgb = subprocess.run(['magick', path, '-depth', '8', 'rgb:-'],
                                 check=True, capture_output=True).stdout
            assert len(rgb) == W * H * 3, '%s is not %dx%d' % (path, W, H)
            index = {}
            def number(c):
                if c not in index:
                    index[c] = len(cols)
                    cols.append(c)
                return index[c]
            for y in range(ROWS):
                full = rgb[int((y + 0.5) * H / ROWS) * W * 3:][:W * 3]
                line = full[:LEFT * 3] + full[(LEFT + 320) * 3:]
                for k in range(0, len(line), 3):
                    menu_px.append(number(line[k:k + 3]))
                edge = full[LEFT * 3:(LEFT + EDGE) * 3] + full[(LEFT + 320 - EDGE) * 3:(LEFT + 320) * 3]
                for k in range(0, len(edge), 3):
                    menu_edge.append(number(edge[k:k + 3]))
            assert len(cols) <= MAX_COLS, '%s: more than %d colours' % (path, MAX_COLS)
            menu_have.append(1)
        else:
            menu_have.append(0)
            menu_px += bytes(ROWS * (LEFT + RIGHT))
            menu_edge += bytes(ROWS * 2 * EDGE)
        menu_cols.append(cols)
    f.write("/* the menu screens' margins (0 intro/main menu, 1 controls/road selection/help):\n"
            " * colour numbers into wide_menu_rgb, [menu][row][left %d | right %d] */\n" % (LEFT, RIGHT))
    f.write("static const unsigned char wide_menu_have[2] = { %s };\n" % ", ".join(map(str, menu_have)))
    f.write("static const unsigned char wide_menu_ncols[2] = { %s };\n" % ", ".join(str(len(c)) for c in menu_cols))
    f.write("static const unsigned char wide_menu_rgb[2][%d][3] = {\n" % MAX_COLS)
    for cols in menu_cols:
        f.write("  { %s },\n" % ", ".join("{%d,%d,%d}" % tuple(c) for c in cols) if cols else "  { {0} },\n")
    f.write("};\n")
    f.write("/* the frame's own outer columns as painted, [menu][row][left %d | right %d] */\n" % (EDGE, EDGE))
    f.write("static const unsigned char wide_menu_edge[2][%d][%d] = {\n" % (ROWS, 2 * EDGE))
    for i in range(0, len(menu_edge), 32):
        f.write(",".join(str(b) for b in menu_edge[i:i + 32]) + ",\n")
    f.write("};\n")
    f.write("static const unsigned char wide_menu[2][%d][%d] = {\n" % (ROWS, max(LEFT + RIGHT, 2)))
    for i in range(0, len(menu_px), 32):
        f.write(",".join(str(b) for b in menu_px[i:i + 32]) + ",\n")
    f.write("};\n")
