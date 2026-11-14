#!/usr/bin/env python3
"""Embed the load image of SKYROADS.EXE (code + initialised data) as image_data.h.

usage: gen_image.py SKYROADS.EXE image_data.h
The image is the part of the MZ file after the header, as DOS loads it.
"""
import struct
import sys

exe, out = sys.argv[1], sys.argv[2]
d = open(exe, 'rb').read()
last, pages = struct.unpack('<HH', d[2:6])
hdr = struct.unpack('<H', d[8:10])[0] * 16
size = pages * 512 - (512 - last if last else 0)
img = d[hdr:size]
with open(out, 'w') as f:
    f.write("/* generated from %s by gen_image.py */\n" % exe.split('/')[-1])
    f.write("static const unsigned char skyroads_image[%d] = {\n" % len(img))
    for i in range(0, len(img), 16):
        f.write("  " + ",".join(str(b) for b in img[i:i+16]) + ",\n")
    f.write("};\n")
print("wrote", out, len(img))
