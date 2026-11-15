#!/usr/bin/env python3
"""Embed the widescreen margins of the painted road backdrops as wide_bg.h.

usage: gen_wide_bg.py DIR wide_bg.h
DIR holds worldN_filled.png (N = 0..9), all the same size: pictures of the
whole widescreen frame, 240 rows tall (the 320x200 screen stretched to 4:3,
rows 1.2x tall) with the original screen in the middle, (width - 320) / 2
columns from the left, and painted on either side.  Only the side margins
are kept, at the game's 200 rows: the PNG row whose middle is nearest each
game row's middle (the inverse of a nearest-neighbour stretch).  The game
shows as much of them as the window's shape leaves room for.
Worlds without a picture are marked missing (platform.c mirrors the
backdrop instead).  Needs ImageMagick (`magick`) to read the PNGs.
"""
import os
import subprocess
import sys

H, ROWS = 240, 200
src, out = sys.argv[1], sys.argv[2]
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
for path in paths:
    if not os.path.exists(path):
        have.append(0)
        data += bytes(ROWS * (LEFT + RIGHT) * 3)
        continue
    rgb = subprocess.run(['magick', path, '-depth', '8', 'rgb:-'],
                         check=True, capture_output=True).stdout
    assert len(rgb) == W * H * 3, '%s is not %dx%d' % (path, W, H)
    have.append(1)
    for y in range(ROWS):
        line = rgb[int((y + 0.5) * H / ROWS) * W * 3:][:W * 3]
        data += line[:LEFT * 3] + line[(LEFT + 320) * 3:]
with open(out, 'w') as f:
    f.write("/* generated from %s by gen_wide_bg.py */\n" % src)
    f.write("#define WIDE_BG_LEFT %d\n#define WIDE_BG_RIGHT %d\n" % (max(LEFT, 1), max(RIGHT, 1)))
    f.write("static const unsigned char wide_bg_have[10] = { %s };\n" % ", ".join(map(str, have)))
    f.write("/* [world][row][left %d | right %d columns][rgb] */\n" % (LEFT, RIGHT))
    f.write("static const unsigned char wide_bg[10][%d][%d][3] = {\n" % (ROWS, max(LEFT + RIGHT, 2)))
    for i in range(0, len(data), 24):
        f.write(",".join(str(b) for b in data[i:i + 24]) + ",\n")
    f.write("};\n")
