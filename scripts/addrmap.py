#!/usr/bin/env python3
"""Map addresses between two builds of SKYROADS.EXE.

The port was decompiled from an early SKYROADS.EXE (build/SKYROADS_unpacked.EXE);
Bluemoon's current release (resources/Skyroads/SKYROADS.EXE, the same file as
SkyRoads Xmas Special's SKYXMAS.EXE) is a lightly revised build of the same
program in which most code and data moved by a few bytes.  This aligns the two
instruction streams and reads, from every pair of matching instructions:

  code: where each instruction (so each function entry) moved
  data: where each data-segment offset moved (memory operands, and immediates
        that point into the data segment, such as file name strings)

usage: addrmap.py OLD.EXE NEW.EXE OLD_FUNCS.c OUT.json
  OLD_FUNCS.c  the Ghidra export of the old build (for its function entries)
Writes {"code": {old: new}, "data": {old: new}, "unmapped_funcs": [...], ...}
with addresses as 4-digit hex strings, and prints a summary.
"""
import collections
import difflib
import json
import re
import struct
import sys

import capstone
from capstone import x86


def load(path):
    d = open(path, 'rb').read()
    hdr = struct.unpack('<H', d[8:10])[0] * 16
    last, pages = struct.unpack('<HH', d[2:6])
    size = pages * 512 - (512 - last if last else 0)
    img = d[hdr:size]
    # the data segment is the one the startup code loads into DS
    m = re.search(rb'(?:\xb8|\xbf)(..)\x8e(?:\xd8|\xdf)', img, re.S)
    ds = struct.unpack('<H', m.group(1))[0] * 16
    return img, ds


def disasm(code):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_16)
    md.detail = True
    out = []
    for i in md.disasm(code, 0):
        norm = i.mnemonic + ' ' + re.sub(r'0x[0-9a-f]+', 'N', i.op_str)
        out.append((i, norm))
    return out


def main():
    old_img, old_ds = load(sys.argv[1])
    new_img, new_ds = load(sys.argv[2])
    funcs = sorted(int(m.group(1), 16) for m in
                   re.finditer(r'// ---- \S+ @ 1000:([0-9a-f]{4})', open(sys.argv[3]).read()))
    A, B = disasm(old_img[:old_ds]), disasm(new_img[:new_ds])
    sm = difflib.SequenceMatcher(None, [a[1] for a in A], [b[1] for b in B], autojunk=False)

    code = {}
    data_votes = collections.defaultdict(collections.Counter)
    call_votes = collections.defaultdict(collections.Counter)
    old_data_len, new_data_len = len(old_img) - old_ds, len(new_img) - new_ds
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'equal':
            continue
        for (a, _), (b, _) in zip(A[i1:i2], B[j1:j2]):
            code[a.address] = b.address
            for oa, ob in zip(a.operands, b.operands):
                if oa.type == x86.X86_OP_MEM and ob.type == x86.X86_OP_MEM:
                    da, db = oa.mem.disp & 0xffff, ob.mem.disp & 0xffff
                    # [disp] or [bx/si/di + disp] in DS; skip bp-relative locals
                    if oa.mem.base not in (x86.X86_REG_BP,) and oa.mem.segment in (0, x86.X86_REG_DS):
                        if da or db:
                            data_votes[da][db] += 1
                elif oa.type == x86.X86_OP_IMM and ob.type == x86.X86_OP_IMM:
                    va, vb = oa.imm & 0xffff, ob.imm & 0xffff
                    if a.mnemonic == 'call' or a.mnemonic.startswith('j'):
                        call_votes[va][vb] += 1
                    elif va != vb and va < 0xc000 and abs(va - vb) < 0x40:
                        # a pointer constant that moved with the data (push 0xd8a)
                        data_votes[va][vb] += 1

    data = {}
    conflicts = []
    for k, c in data_votes.items():
        (v, n), = c.most_common(1)
        data[k] = v
        if len(c) > 1:
            conflicts.append((k, dict(c)))
    func_map, unmapped = {}, []
    for f in funcs:
        if f in code:
            func_map[f] = code[f]
        elif f in call_votes:
            func_map[f] = call_votes[f].most_common(1)[0][0]
        else:
            unmapped.append(f)

    out = {
        "old_ds": "%04x" % old_ds, "new_ds": "%04x" % new_ds,
        "code": {"%04x" % k: "%04x" % v for k, v in sorted(func_map.items())},
        "data": {"%04x" % k: "%04x" % v for k, v in sorted(data.items())},
        "unmapped_funcs": ["%04x" % f for f in unmapped],
        "data_conflicts": [["%04x" % k, {"%04x" % a: n for a, n in c.items()}] for k, c in conflicts],
        "match_ratio": round(sm.ratio(), 4),
    }
    json.dump(out, open(sys.argv[4], 'w'), indent=1)
    shifts = collections.Counter((int(v, 16) - int(k, 16)) for k, v in out["data"].items())
    print("instructions matched: %.1f%%" % (100 * sm.ratio()))
    print("functions mapped: %d of %d (unmapped: %s)" % (len(func_map), len(funcs), out["unmapped_funcs"]))
    print("data offsets mapped: %d, conflicts: %d" % (len(data), len(conflicts)))
    print("data shifts (new - old): %s" % shifts.most_common(8))


if __name__ == '__main__':
    main()
