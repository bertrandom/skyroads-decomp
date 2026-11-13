#!/usr/bin/env python3
import re
defs = {}
for f in ["runtime.c", "manual.c", "video.c", "render.c", "audio.c"]:
    t = open(f).read()
    for m in re.finditer(r"^[A-Za-z_][\w \*]*?\b(FUN_1000_[0-9a-f]{4})\(([^)]*)\)\s*\n?\{", t, re.M):
        p = m.group(2).strip()
        n = 0 if p in ("", "void") else len(p.split(","))
        defs[m.group(1)] = n
g = open("game.c").read()
def args_of(s, i):
    depth, j, cur, out = 0, i, "", []
    while j < len(s):
        ch = s[j]
        if ch == "(":
            depth += 1
            if depth == 1: j += 1; continue
        elif ch == ")":
            depth -= 1
            if depth == 0: break
        if ch == "," and depth == 1: out.append(cur); cur = ""
        else: cur += ch
        j += 1
    if cur.strip(): out.append(cur)
    return out
for m in re.finditer(r"\b(FUN_1000_[0-9a-f]{4})\s*\(", g):
    name = m.group(1)
    if name not in defs: continue
    a = args_of(g, m.end() - 1)
    if len(a) != defs[name]:
        line = g.count("\n", 0, m.start()) + 1
        print("%5d %s: got %d want %d :: %s" % (line, name, len(a), defs[name], g[m.start():m.start()+90].split("\n")[0]))
