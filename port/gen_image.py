#!/usr/bin/env python3
import sys
exe = sys.argv[1]; out = sys.argv[2]
d = open(exe,'rb').read()
img = d[0x200:0x200+0x7570]
with open(out,'w') as f:
    f.write("/* generated from %s */\n" % exe)
    f.write("static const unsigned char skyroads_image[%d] = {\n" % len(img))
    for i in range(0,len(img),16):
        f.write("  " + ",".join(str(b) for b in img[i:i+16]) + ",\n")
    f.write("};\n")
print("wrote",out,len(img))
