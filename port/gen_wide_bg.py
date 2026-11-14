#!/usr/bin/env python3
"""Embed the widescreen margins of the filled road backdrops as wide_bg.h.

usage: gen_wide_bg.py DIR wide_bg.h
DIR holds worldN_filled.png (N = 0..9): 426x240 pictures of the whole
widescreen frame, the 320x200 screen stretched to 4:3 (rows 1.2x tall) in
the middle and painted on either side.  Only the side margins (53 columns
each) are kept, at the game's 200 rows: the PNG row whose middle is nearest
each game row's middle (the inverse of a nearest-neighbour stretch).
Worlds without a picture are marked missing (platform.c mirrors the
backdrop instead).  Needs ImageMagick (`magick`) to read the PNGs.
"""
import os
import subprocess
import sys

W, H, ROWS, MARGIN = 426, 240, 200, 53
src, out = sys.argv[1], sys.argv[2]
have = []
data = bytearray()
for n in range(10):
    path = os.path.join(src, 'world%d_filled.png' % n)
    if not os.path.exists(path):
        have.append(0)
        data += bytes(ROWS * MARGIN * 2 * 3)
        continue
    rgb = subprocess.run(['magick', path, '-resize', '%dx%d!' % (W, H), '-depth', '8', 'rgb:-'],
                         check=True, capture_output=True).stdout
    assert len(rgb) == W * H * 3, path
    have.append(1)
    for y in range(ROWS):
        line = rgb[int((y + 0.5) * H / ROWS) * W * 3:][:W * 3]
        data += line[:MARGIN * 3] + line[(W - MARGIN) * 3:]
with open(out, 'w') as f:
    f.write("/* generated from %s by gen_wide_bg.py */\n" % src)
    f.write("#define WIDE_BG_MARGIN %d\n" % MARGIN)
    f.write("static const unsigned char wide_bg_have[10] = { %s };\n" % ", ".join(map(str, have)))
    f.write("/* [world][row][left 53 | right 53 columns][rgb] */\n")
    f.write("static const unsigned char wide_bg[10][%d][%d][3] = {\n" % (ROWS, MARGIN * 2))
    for i in range(0, len(data), 24):
        f.write(",".join(str(b) for b in data[i:i + 24]) + ",\n")
    f.write("};\n")
