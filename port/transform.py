#!/usr/bin/env python3
"""Turn the Ghidra pseudo-C in ../build/skyroads.c into compilable native C.

The original is a 16-bit small/medium model DOS program.  We keep its flat
data-segment memory model: every literal DS offset becomes an access into
g_ds (which points into the flat g_mem array), and near pointers become real
C pointers into g_ds.

Functions that rely on the raw CPU registers (the compiler runtime, BIOS and
DOS wrappers, and the hand written VGA rasteriser) are skipped here and
provided by hand in runtime.c / video.c.
"""
import re

SRC = "../build/skyroads.c"
OUT_C = "game.c"
OUT_H = "game.h"

MANUAL = set("""
FUN_1000_00bb FUN_1000_03c2 FUN_1000_3f91 FUN_1000_3fe2 FUN_1000_4084 FUN_1000_4331 FUN_1000_4485 FUN_1000_4b43
FUN_1000_5614 FUN_1000_57c4
FUN_1000_0eeb FUN_1000_0f62 FUN_1000_0f8c FUN_1000_1073 FUN_1000_1191 FUN_1000_11d3
FUN_1000_2b0f FUN_1000_4052 FUN_1000_41a0 FUN_1000_4201 FUN_1000_3acc FUN_1000_3b6b
FUN_1000_6006 FUN_1000_60ee FUN_1000_0046 FUN_1000_5e5a FUN_1000_0c98
FUN_1000_58a5 FUN_1000_58cd FUN_1000_5b76 FUN_1000_5bc0 FUN_1000_05f6
FUN_1000_0000 FUN_1000_0672 FUN_1000_068b FUN_1000_06a4 FUN_1000_06b9
FUN_1000_0ed0 FUN_1000_2cce FUN_1000_2d1f FUN_1000_34ae FUN_1000_39d4
FUN_1000_3a22 FUN_1000_3a3f FUN_1000_3a96 FUN_1000_3b9d FUN_1000_3c03
FUN_1000_3c52 FUN_1000_3c9a FUN_1000_3cb1 FUN_1000_3d18 FUN_1000_3d9e
FUN_1000_3e0f FUN_1000_3e4c FUN_1000_3e8a FUN_1000_5892 FUN_1000_5919
FUN_1000_59cf FUN_1000_5a98 FUN_1000_5b39 FUN_1000_5bdb FUN_1000_5bf8
FUN_1000_5c36 FUN_1000_5c59 FUN_1000_5c6a FUN_1000_5c77 FUN_1000_5c96
FUN_1000_5ca6 FUN_1000_5cd1 FUN_1000_5ce3 FUN_1000_5d07 FUN_1000_5d1b
FUN_1000_5d33 FUN_1000_5d4c FUN_1000_5d80 FUN_1000_5d8c FUN_1000_5dee
FUN_1000_5c82 FUN_1000_5f7d FUN_1000_5fcc FUN_1000_5fd4 FUN_1000_5feb
FUN_1000_6001 FUN_1000_6053 FUN_1000_60e9
FUN_1000_601d FUN_1000_6027 FUN_1000_603b FUN_1000_609f FUN_1000_60ab
FUN_1000_6151 FUN_1000_6168 FUN_1000_61e4 entry
FUN_1000_5ef6 FUN_1000_5f0c FUN_1000_5f52 FUN_1000_5fb5
FUN_1000_630f FUN_1000_6326 FUN_1000_633d FUN_1000_6350 FUN_1000_6364
FUN_1000_63a3 FUN_1000_63bf FUN_1000_63d3 FUN_1000_63f0 FUN_1000_6420
FUN_1000_644a FUN_1000_6490 FUN_1000_6499 FUN_1000_64ab FUN_1000_64ff
FUN_1000_6576 FUN_1000_6595 FUN_1000_65e0 FUN_1000_661f FUN_1000_6645
FUN_1000_6679 FUN_1000_669c FUN_1000_66e6
""".split())

TYPE_MAP = {
    "undefined1": "uint8_t", "undefined2": "uint16_t", "undefined4": "uint32_t",
    "byte": "uint8_t", "sbyte": "int8_t", "uint": "uint16_t", "ulong": "uint32_t",
    "long": "int32_t", "int": "int16_t", "char": "char", "bool": "bool",
    "void": "void", "code": "void",
}
TYPE_RE = re.compile(r"\b(" + "|".join(TYPE_MAP) + r")\b")
DECL_PTR_RE = re.compile(r"\*\s*([A-Za-z_]\w*)")
RAM_RE = re.compile(r"\b([a-z]*)Ram([0-9a-fA-F]{8})\b")
DAT_RE = re.compile(r"\bDAT_([0-9a-fA-F]{4})_([0-9a-fA-F]+)\b")
RAM_TYPES = {"u": "uint16_t", "b": "uint8_t", "i": "int16_t", "c": "char"}

# bare deref of a literal:  *(TYPE *)0xADDR
LIT_RE = re.compile(
    r"\*\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*(\*+)\s*\)\s*0x([0-9a-fA-F]+)\b")
# pointer cast of a literal:  (TYPE *)0xADDR
CASTLIT_RE = re.compile(
    r"\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*(\*+)\s*\)\s*0x([0-9a-fA-F]+)\b")
# start of a computed pointer cast/deref:  *(TYPE *)(   -- handled with a scanner
STARTER_RE = re.compile(
    r"\*\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*(\*+)\s*\)\s*\(\s*")


def type_sub(t):
    return TYPE_RE.sub(lambda m: TYPE_MAP[m.group(1)], t)


def lit_sub(t):
    t = LIT_RE.sub(lambda m: "*(volatile %s %s)(g_ds + 0x%x)" %
                   (m.group(1), m.group(2), int(m.group(3), 16)), t)
    t = CASTLIT_RE.sub(lambda m: "((%s %s)(g_ds + 0x%x))" %
                       (m.group(1), m.group(2), int(m.group(3), 16)), t)
    return t


def match_paren(s, i):
    """i points at '('.  Return index just past matching ')'."""
    depth = 0
    while i < len(s):
        if s[i] == "(":
            depth += 1
        elif s[i] == ")":
            depth -= 1
            if depth == 0:
                return i + 1
        i += 1
    return i


def computed_sub(t, ptr_vars):
    out = []
    i = 0
    while True:
        m = STARTER_RE.search(t, i)
        if not m:
            out.append(t[i:])
            break
        out.append(t[i:m.start()])
        typ, stars = m.group(1), m.group(2)
        paren = m.end() - 1
        end = match_paren(t, paren)
        expr = t[paren + 1:end - 1].strip()
        first = re.match(r"([A-Za-z_]\w*)", expr)
        native = (first and first.group(1) in ptr_vars) or \
                 expr.startswith(("(ulong)", "(uint32_t)", "(long)",
                                  "g_ds", "g_mem", "g_", "_frame", "DS_ADDR",
                                  "CS_ADDR", "MEM_ADDR"))
        if native:
            out.append(t[m.start():end])
        else:
            out.append("*(volatile %s %s)(g_ds + (uint16_t)(%s))" % (typ, stars, expr))
        i = end
    return "".join(out)


def _dat_rep(m):
    seg, off = m.group(1), int(m.group(2), 16)
    if seg == "1000":
        base = "g_mem + 0x%x" % (0x10000 + off)
    elif seg == "1676":
        base = "g_ds + 0x%x" % off
    else:
        base = "g_mem + 0x%x" % (int(seg, 16) * 16 + off)
    return "(*(uint16_t *)(%s))" % base


def misc_sub(t):
    t = DAT_RE.sub(_dat_rep, t)
    t = RAM_RE.sub(lambda m: "(*(%s *)(g_mem + 0x%s))" %
                   (RAM_TYPES.get(m.group(1), "uint16_t"), m.group(2)), t)
    t = t.replace("in(", "port_in(").replace("out(", "port_out(")
    t = re.sub(r"&\s*stack0x[0-9a-fA-F]+", "&g_stack_dummy", t)
    return t


def signature(body):
    """Extract the C function signature (everything before the first '{')."""
    idx = body.find("{")
    if idx < 0:
        return None
    sig = body[:idx]
    # drop comments
    sig = re.sub(r"/\*.*?\*/", "", sig, flags=re.S)
    sig = re.sub(r"//[^\n]*", "", sig)
    sig = " ".join(sig.split())
    return sig




def strip_comments(text):
    out = []
    i, n = 0, len(text)
    state = "code"
    while i < n:
        c = text[i]
        if state == "code":
            if text.startswith("//", i):
                state = "lc"; i += 2; continue
            if text.startswith("/*", i):
                state = "bc"; i += 2; continue
            out.append(c); i += 1
        elif state == "lc":
            if c == "\n":
                state = "code"; out.append(c)
            i += 1
        elif state == "bc":
            if text.startswith("*/", i):
                state = "code"; i += 2; continue
            if c == "\n":
                out.append(c)
            i += 1
    return "".join(out)

def _split_params(params):
    out, depth, cur = [], 0, ""
    for ch in params:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def to_kr(text):
    """Convert an ANSI function definition to old-style (K&R) form so that
    later calls are not checked against the recovered prototype."""
    brace = text.find("{")
    if brace < 0:
        return text
    head, tail = text[:brace], text[brace:]
    open_paren = head.find("(")
    if open_paren < 0:
        return text
    depth, i = 0, open_paren
    while i < len(head):
        if head[i] == "(":
            depth += 1
        elif head[i] == ")":
            depth -= 1
            if depth == 0:
                break
        i += 1
    prefix = head[:open_paren].strip()
    params = head[open_paren + 1:i].strip()
    if params == "" or params == "void":
        return prefix + "()" + tail
    decls, names = [], []
    for p in _split_params(params):
        p = p.strip()
        m = re.search(r"([A-Za-z_]\w*)\s*(\[.*\])?$", p)
        if not m:
            continue
        name = m.group(1)
        typ = p[:m.start(1)].strip()
        names.append(name)
        decls.append(typ + " " + name + ";")
    # Pointer parameters may arrive as 16-bit DS offsets: normalise them.
    conv = []
    for d, n in zip(decls, names):
        if "*" in d:
            typ = d[:d.rfind(n)].strip()
            conv.append("  %s = (%s)near_ptr((uintptr_t)%s);" % (n, typ, n))
    body = tail
    if conv:
        brace = body.find("{")
        body = body[:brace + 1] + "\n" + "\n".join(conv) + body[brace + 1:]
    return (prefix + "(" + ", ".join(names) + ")\n  " +
            "\n  ".join(decls) + "\n" + body)


# Textual fixes for call sites where Ghidra lost stack arguments.
FIXUPS = [
    ("FUN_1000_5fb5(uVar4);", "FUN_1000_5fb5(uVar4,0,uVar5,0x7d64);"),
    ("FUN_1000_5fb5(uVar1);", "FUN_1000_5fb5(uVar1,0,*(volatile uint16_t *)(g_ds + 0x4560),0x7d64);"),
    ("FUN_1000_6420(uVar1);", "FUN_1000_6420(uVar1,0,0x1000,0);"),
    # 1000:5d80 shifts DX:AX left by CL (register args); both callers do [0x41c0] << 16
    ("FUN_1000_5d80()", "((uint32_t)*(volatile uint16_t *)(g_ds + 0x41c0) << 16)"),
    ("FUN_1000_5d8c(uVar4,iVar1 + -3,uVar7)", "FUN_1000_5d8c(uVar4,iVar1 + -3,(uint16_t)uVar7,(uint16_t)(uVar7 >> 16))"),
    # 1000:2b3d: the last three 2d1f args were attributed to the 0baf call
    ("iVar1 = FUN_1000_0baf(0,0x2800,1,0,iVar1);", "int16_t p8_dst = iVar1;\n  iVar1 = FUN_1000_0baf(0,0x2800);"),
    ("*(volatile uint16_t *)(g_ds + 0xaf36));\n  FUN_1000_4b8e(0x41c2,1,0x24);",
     "*(volatile uint16_t *)(g_ds + 0xaf36),1,0,p8_dst);\n  FUN_1000_4b8e(0x41c2,1,0x24);"),
    ("piVar1 = (int16_t *)(*(volatile int16_t *)(g_ds + 0x9332) * 2 + 0x451c);",
     "piVar1 = (int16_t *)near_ptr((uint16_t)(*(volatile int16_t *)(g_ds + 0x9332) * 2 + 0x451c));"),
    ("*(int16_t *)*(volatile uint16_t *)(g_ds + 0xbd0)", "*(int16_t *)near_ptr(*(volatile uint16_t *)(g_ds + 0xbd0))"),
    # 1000:186b: the 1631 args were attributed to the preceding 04c0 call
    ("uVar4 = FUN_1000_04c0(param_1,param_2,param_3 + (*(int16_t *)(_frame + 4)),0x2f - (*(uint16_t *)(_frame + 6)),param_4);\n      iVar3 = FUN_1000_1631(uVar4);",
     "uVar4 = FUN_1000_04c0(param_1,param_2,param_3 + (*(int16_t *)(_frame + 4)));\n      iVar3 = FUN_1000_1631(uVar4,0x2f - (*(uint16_t *)(_frame + 6)),param_4);"),
    ("FUN_1000_6168(0xbe,3,0x53ae);", "FUN_1000_6168(0xbe,3,0x53ae,0x1676);"),
]


# functions taking a 32-bit value as two 16-bit arguments: name -> arg count
LONG_FUNCS = {"FUN_1000_5d8c": 4, "FUN_1000_5d4c": 4, "FUN_1000_5dee": 4,
              "FUN_1000_5e5a": 4, "FUN_1000_1732": 4, "FUN_1000_1c62": 3}


def split_long_args(text):
    """32-bit helpers take (a_lo, a_hi, b_lo, b_hi); Ghidra sometimes merged
    `a` into one 32-bit argument, giving 3 args.  Split it again."""
    out, i = [], 0
    pat = re.compile(r"\b(%s)\s*\(" % "|".join(LONG_FUNCS))
    while True:
        m = pat.search(text, i)
        if not m:
            out.append(text[i:]); break
        end = match_paren(text, m.end() - 1)
        args = _split_params(text[m.end():end - 1])
        if len(args) == LONG_FUNCS[m.group(1)] - 1 and "uVar7 >> 16" not in text[m.start():end]:
            a = args[0].strip()
            args = ["(uint16_t)(%s)" % a, "(uint16_t)((uint32_t)(%s) >> 16)" % a] + args[1:]
            out.append(text[i:m.end()] + ",".join(args) + ")")
        else:
            out.append(text[i:end])
        i = end
    return "".join(out)


def fixup_calls(text, param_map):
    """Wrap literal DS offsets passed to pointer parameters of transformed
    functions with a real pointer into g_ds."""
    out = []
    i = 0
    pat = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
    while True:
        m = pat.search(text, i)
        if not m:
            out.append(text[i:])
            break
        name = m.group(1)
        if name not in param_map:
            out.append(text[i:m.end()])
            i = m.end()
            continue
        end = match_paren(text, m.end() - 1)
        args = text[m.end():end - 1]
        types = param_map[name]
        # split top-level commas
        pieces, depth, cur = [], 0, ""
        for ch in args:
            if ch in "([":
                depth += 1
            elif ch in ")]":
                depth -= 1
            if ch == "," and depth == 0:
                pieces.append(cur); cur = ""
            else:
                cur += ch
        if args.strip():
            pieces.append(cur)
        newargs = []
        for k, p in enumerate(pieces):
            sp = p.strip()
            mm = re.fullmatch(r"0x([0-9a-fA-F]+)", sp)
            if mm and k < len(types) and types[k]:
                newargs.append("(uint8_t *)(g_ds + 0x%s)" % mm.group(1))
            else:
                newargs.append(p)
        out.append(text[i:m.end()] + ",".join(newargs) + ")")
        i = end
    return "".join(out)


LOCAL_DECL_RE = re.compile(
    r"^[ \t]*((?:volatile\s+)?(?:u?int(?:8|16|32)_t|char|bool|void))\s*(\*?)\s*\b(local_([0-9a-fA-F]+))\s*(\[\s*(\d+)\s*\])?\s*;[ \t]*\n",
    re.M)
LTYPE_SIZE = {"uint8_t": 1, "int8_t": 1, "char": 1, "bool": 1, "uint16_t": 2,
              "int16_t": 2, "uint32_t": 4, "int32_t": 4}


def frame_locals(body):
    """Ghidra splits stack structures into separate locals (local_N lives at
    frame offset -N).  Recreate the real frame so writes through a pointer to
    one local can spill into its neighbours, exactly like the original."""
    decls = list(LOCAL_DECL_RE.finditer(body))
    if not decls:
        return body
    info = {}
    top = 0
    for m in decls:
        typ, star, name, off = m.group(1).strip(), m.group(2), m.group(3), int(m.group(4), 16)
        arr = m.group(5) is not None
        info[name] = (typ + (" *" if star else ""), arr, off)
        top = max(top, off)
    size = top + 8
    for m in reversed(decls):
        body = body[:m.start()] + body[m.end():]
    # insert the frame declaration after the opening brace
    brace = body.find("{")
    body = (body[:brace + 1] + "\n  uint16_t _fsave __attribute__((cleanup(ds_frame_release)));\n  uint8_t *_frame = ds_frame_alloc(%d, &_fsave);" % size +
            body[brace + 1:])
    def rep(m):
        typ, arr, off = info[m.group(0)]
        if arr:
            return "((%s *)(_frame + %d))" % (typ, top + 4 - off)
        return "(*(%s *)(_frame + %d))" % (typ, top + 4 - off)
    names = sorted(info, key=len, reverse=True)
    pat = re.compile(r"\b(" + "|".join(map(re.escape, names)) + r")\b")
    head, rest = body[:brace + 1], body[brace + 1:]
    return head + pat.sub(rep, rest)

def main():
    src = open(SRC).read()
    lines = src.split("\n")
    blocks, cur = [], None
    for ln in lines:
        m = re.match(r"// ---- (\S+) @ 1000:([0-9a-f]{4}) ----", ln)
        if m:
            if cur:
                blocks.append(cur)
            cur = {"name": m.group(1), "off": int(m.group(2), 16), "body": []}
        elif cur is not None:
            cur["body"].append(ln)
    if cur:
        blocks.append(cur)

    decls = []
    for b in blocks:
        if b["name"] in MANUAL:
            continue
        sig = signature("\n".join(b["body"]))
        if sig:
            # Use a prototype-less declaration so the many places where the
            # decompiler lost/synthesised arguments still compile.
            head = sig.split("(", 1)[0].strip()
            decls.append(type_sub(head) + "();")

    rt = open("runtime.h").read()
    for b in blocks:
        if b["name"] not in MANUAL or b["name"] == "entry":
            continue
        if re.search(r"\b%s\s*\(" % b["name"], rt):
            continue
        sig = signature("\n".join(b["body"]))
        if sig:
            head = type_sub(sig.split("(", 1)[0].strip())
            ret = head.rsplit(" ", 1)[0].replace("__cdecl16near", "").replace("__cdecl16far", "").strip()
            decls.append("%s %s();  /* manual */" % (ret, b["name"]))
    header = ["/* Generated by transform.py -- do not edit. */",
              "#ifndef SKYROADS_GAME_H", "#define SKYROADS_GAME_H",
              '#include "compat.h"', ""]
    header += decls
    header += ["", "#endif"]
    open(OUT_H, "w").write("\n".join(header))

    out = ['/* Generated by transform.py -- do not edit. */',
           '#include "compat.h"', '#include "game.h"', '#include "runtime.h"', ""]
    param_map = {}
    for b in blocks:
        if b["name"] in MANUAL:
            continue
        body = "\n".join(b["body"])
        _sig = type_sub(signature(body) or "")
        _p = _sig.split("(", 1)
        if len(_p) == 2:
            _args = _p[1].rsplit(")", 1)[0].strip()
            if _args and _args != "void":
                types = []
                for a in _split_params(_args):
                    types.append("*" in a)
                param_map[b["name"]] = types
        ptr_vars = set(DECL_PTR_RE.findall(body))
        body = strip_comments(body)
        body = type_sub(body)
        body = to_kr(body)
        body = frame_locals(body)
        body = lit_sub(body)
        body = computed_sub(body, ptr_vars)
        body = misc_sub(body)
        # Ghidra's synthetic incoming-register locals are replaced by macros.
        body = re.sub(r"^\s*(?:uint8_t|uint16_t|uint32_t|int16_t|int32_t|char|bool)\s+unaff_(?:DS|ES|SS)\s*;\s*$",
                      "", body, flags=re.M)
        out.append(body)
        out.append("")
    text = "\n".join(out)
    text = fixup_calls(text, param_map)
    for old, new in FIXUPS:
        if old not in text:
            print("warning: fixup not applied:", old)
        text = text.replace(old, new)
    text = split_long_args(text)
    # 16-bit unsigned additions with a U-suffixed constant must wrap
    text = re.sub(r"\(([A-Za-z_]\w*) \+ (0x[0-9a-fA-F]+)U\)", r"((uint16_t)(\1 + \2U))", text)
    open(OUT_C, "w").write(text)
    print("wrote %s and %s (%d declarations)" % (OUT_C, OUT_H, len(decls)))


if __name__ == "__main__":
    main()
