#!/usr/bin/env python3
"""Rewrite the hand-written port from the early SKYROADS.EXE to Bluemoon's build.

Uses build/addrmap.json (scripts/addrmap.py) to move, in port/*.c and *.h
(not the generated game.c / game.h / protos.h / image_data.h):

  FUN_1000_xxxx names          -> the same function in the new build
  "1000:xxxx" in comments      -> the new code address
  data-segment addresses       -> new data address (only the addresses listed
                                  in DATA_ADDRS: the ones the port uses, so
                                  sizes, VGA ports and the like are untouched)
  the data segment 0x1676      -> 0x166e, the stack segment 0x218a -> 0x2183

usage: rebase_port.py [--write]      (prints every change; --write applies)
"""
import bisect
import json
import os
import re
import sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
MAP = json.load(open(os.path.join(ROOT, "build/addrmap.json")))
SKIP = {"game.c", "game.h", "protos.h", "image_data.h", "relay_key.h"}

FUNC = {int(k, 16): int(v, 16) for k, v in MAP["code"].items()}
DIRECT = {int(k, 16): int(v, 16) for k, v in MAP["data"].items()}
# initialised data moved in blocks (byte alignment of the two data images)
INIT_BLOCKS = [(0x0006, 0x00f0, -6), (0x011a, 0x0c08, -48), (0x0c08, 0x0e1c, 12)]
# code addresses the decompile stores as function pointers are not data
NOT_DATA = {0x309f, 0x3153, 0x3190, 0x31db, 0x3c3e, 0x3c47, 0x41e7, 0x58a1, 0x5d84}

# every data-segment address the hand-written port uses (found by grepping
# DS16/DS8/g_ds forms and pointer arguments; see the rebase notes)
DATA_ADDRS = [int(a, 16) for a in """
003c 003e 011a 0162 0352 0353 047a 068e 0ba7 0baf 0bd0 0bd2 0bf2 0c10 0c1b 0c26
0c31 0c3c 0c6b 0c77 0c83 0c84 0cb0 0cb6 0cb8 0cfc 0d52 0d8a 0e08 0e11 0e12 0e1b
0e1c 0e1e 0e20 0e22 0e24 0e26 0e28 0e2a 0e2c 0e2e 0e30 0e32 0e34 0e36 0e38 0e3a
0e3c 0e3e 0e44 0e46 0e48 0e4a 0e4c 0e4e 0e50 0e52 0e54 0e56 0e58 0e5a 0e5c 0e5e
0e60 0e62 0e64 0e66 0e68 0e6a 0e6c 0e6e 0e70 0e72 0e76 0e86 113e 1243 14fb 1600
162c 3184 3186 3188 318a 318c 318e 3192 3194 3196 3198 319a 319b 31a6 31a8 41aa
41ac 41ae 41b0 41b2 41b4 41b6 41b8 41ba 41bb 41bc 41c0 41c2 4512 4514 451a 451c
4560 4562 4566 456a 456e 45b6 45b8 5170 5174 5478 54a0 54a2 54b0 9332 9334 9336
5488 53ae 95f6 9612 9614 9618 961a 961c af1c af2a af2c af34 af36 af38 af3a af3c b140
""".split()]
SEGS = {0x1676: 0x166e, 0x218a: 0x2183}
CODE_CONSTS = {0x34a7, 0x3153, 0x3190, 0x325b}     # render.c: DS:0xe38..0xe3e


def data_map(a):
    if a in DIRECT and a not in NOT_DATA:
        return DIRECT[a]
    for lo, hi, s in INIT_BLOCKS:
        if lo <= a < hi:
            return a + s
    keys = sorted(k for k in DIRECT if k not in NOT_DATA)
    i = bisect.bisect_left(keys, a)
    lo, hi = keys[i - 1], keys[i]
    s1, s2 = DIRECT[lo] - lo, DIRECT[hi] - hi
    if s1 != s2:
        raise SystemExit("ambiguous data address %04x (%+d below, %+d above)" % (a, s1, s2))
    return a + s1


def code_map(a):
    """an instruction address: the nearest function entry at or below, same offset"""
    entries = sorted(FUNC)
    f = entries[bisect.bisect_right(entries, a) - 1]
    return FUNC[f] + (a - f)


DATA = {a: data_map(a) for a in DATA_ADDRS}


def fmt(old_tok, new_val):
    """keep the token's style: case, width, 0x prefix"""
    digits = old_tok[2:]
    s = "%0*x" % (len(digits), new_val) if digits[0] == "0" else "%x" % new_val
    return "0x" + (s.upper() if digits.isupper() else s)


def rewrite(text):
    changes = []

    def fun(m):
        old = int(m.group(1), 16)
        if old not in FUNC:
            return m.group(0)
        new = "FUN_1000_%04x" % FUNC[old]
        if new != m.group(0):
            changes.append((m.group(0), new))
        return new
    text = re.sub(r"\bFUN_1000_([0-9a-f]{4})\b", fun, text)

    def cref(m):
        new = "1000:%04x" % code_map(int(m.group(1), 16))
        if new != m.group(0):
            changes.append((m.group(0), new))
        return new
    text = re.sub(r"\b1000:([0-9a-f]{4})\b", cref, text)

    def hexnum(m):
        tok = m.group(0)
        v = int(tok, 16)
        line_start = text.rfind("\n", 0, m.start()) + 1
        line = text[line_start:text.find("\n", m.start())]
        if v in SEGS:
            new = fmt(tok, SEGS[v])
        elif v in CODE_CONSTS and "DS16(0xe3" in line:
            new = fmt(tok, code_map(v))
        elif v in DATA:
            new = fmt(tok, DATA[v])
        else:
            return tok
        if new != tok:
            changes.append((tok, new))
        return new
    text = re.sub(r"\b0[xX][0-9a-fA-F]{3,4}(?![0-9a-fA-FuU]*[0-9a-fA-F])", hexnum, text)

    # two-digit data addresses only as the direct argument of DS16()/DS8()
    def small(m):
        v = int(m.group(2), 16)
        if v not in DATA:
            return m.group(0)
        new = m.group(1) + fmt(m.group(2), DATA[v])
        changes.append((m.group(0), new))
        return new
    text = re.sub(r"(\bDS(?:16|8)\(\s*)(0x[0-9a-fA-F]{2})(?=\s*[)+])", small, text)
    return text, changes


def main():
    write = "--write" in sys.argv
    port = os.path.join(ROOT, "port")
    total = 0
    for name in sorted(os.listdir(port)):
        if not name.endswith((".c", ".h")) or name in SKIP:
            continue
        path = os.path.join(port, name)
        old = open(path).read()
        new, changes = rewrite(old)
        if not changes:
            continue
        total += len(changes)
        summary = {}
        for a, b in changes:
            summary[(a, b)] = summary.get((a, b), 0) + 1
        print("%s: %d changes" % (name, len(changes)))
        for (a, b), n in sorted(summary.items()):
            print("   %-15s -> %-15s x%d" % (a, b, n))
        if write:
            open(path, "w").write(new)
    print("%d changes%s" % (total, "" if write else " (dry run; --write to apply)"))


if __name__ == "__main__":
    main()
