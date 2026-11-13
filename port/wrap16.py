#!/usr/bin/env python3
"""Restore 16-bit integer semantics in the generated game code.

The original program was compiled for a 16-bit int.  Ghidra's output uses
those rules implicitly: `uint + uint` is a 16-bit unsigned value, a uint
compared with an int is an unsigned comparison, `0xde00` is an unsigned
16-bit constant.  Compiled as normal C (32-bit int) the same text promotes
everything to int, so e.g. `(param_3 + 0xde00) / 0x80` no longer wraps and
`uVar == -1` is never true.

This pass walks Clang's typed AST of game.c, computes for each expression the
type it had under 16-bit C rules, and inserts casts where 32-bit C would
behave differently:

  R1  16-bit arithmetic (+ - * << unary - ~, and & | ^ mixing signedness)
      whose result is not already truncated gets `(uint16_t)(...)` /
      `(int16_t)(...)`.
  R2  relational / equality / division / modulo operators whose 16-bit
      operands combine to unsigned get their signed operands cast to
      `(uint16_t)`.

usage: wrap16.py game.c   (rewrites the file in place, prints a summary)
"""
import json
import os
import subprocess
import sys

NARROW = {"u8", "s8", "u16", "s16"}
# Ghidra prints constants at their varnode size, so a literal takes the width
# of whatever it is combined with: "L" = fits in 16 bits signed (incl.
# negated literals), "LU" = 0x8000..0xffff (unsigned 16-bit in a 16-bit
# context, a plain value in a 32-bit one).
LITS = {"L", "LU"}


def ctype(qual):
    """Map a Clang qualType string to a 16-bit-C type class."""
    q = qual.replace("volatile ", "").replace("const ", "").strip()
    if "*" in q or "[" in q:
        return "p"
    return {
        "uint16_t": "u16", "unsigned short": "u16",
        "int16_t": "s16", "short": "s16",
        "uint8_t": "u8", "unsigned char": "u8",
        "int8_t": "s8", "signed char": "s8", "char": "s8",
        "bool": "s8", "_Bool": "s8",
        "uint32_t": "u32", "int32_t": "s32",
    }.get(q, "w")          # int, long, uintptr_t, ... : wide, leave alone


def promote(t):
    if t == "LU":
        return "u16"
    return "s16" if t in ("u8", "s8", "L") else t


def usual(a, b):
    if "p" in (a, b):
        return "p"
    if a in LITS and b in LITS:
        return promote(a if a == "LU" else b)
    if a in LITS or b in LITS:
        lit, other = (a, b) if a in LITS else (b, a)
        if other not in NARROW:
            return other                  # literal adopts the wide type
        return "u16" if lit == "LU" or promote(other) == "u16" else "s16"
    if a not in NARROW or b not in NARROW:
        if "u32" in (a, b):
            return "u32"
        return "w" if "w" in (a, b) else "s32"
    a, b = promote(a), promote(b)
    return "u16" if "u16" in (a, b) else "s16"


def in_macro(node):
    r = node.get("range", {})
    for k in ("begin", "end"):
        loc = r.get(k, {})
        if "spellingLoc" in loc or "expansionLoc" in loc or "offset" not in loc:
            return True
    return False


def span(node):
    r = node["range"]
    return r["begin"]["offset"], r["end"]["offset"] + r["end"]["tokLen"]


def is_literal(n):
    """A (possibly negated / parenthesised / implicitly cast) integer literal?"""
    while n.get("kind") in ("ParenExpr", "ImplicitCastExpr"):
        n = n["inner"][0]
    if n.get("kind") == "UnaryOperator" and n.get("opcode") == "-":
        return is_literal(n["inner"][0]) and "neg"
    return n.get("kind") in ("IntegerLiteral", "CharacterLiteral") and "pos"


class Pass:
    def __init__(self, src):
        self.src = src
        self.edits = []        # (begin, end, prefix)
        self.r1 = self.r2 = 0

    def wrap(self, node, prefix):
        if in_macro(node):
            return
        b, e = span(node)
        self.edits.append((b, e, prefix))

    def type16(self, n):
        k = n.get("kind")
        inner = n.get("inner", [])
        qual = n.get("type", {}).get("qualType", "")
        if k == "IntegerLiteral":
            v = int(n["value"])
            b, e = span(n) if not in_macro(n) else (0, 0)
            text = self.src[b:e].lower()
            if v <= 0x7fff:
                return "L"
            if v <= 0xffff and (text.startswith("0x") or qual == "unsigned int"):
                return "LU"
            return "w"
        if k == "CharacterLiteral":
            return "s8"
        if k == "ParenExpr":
            return self.type16(inner[0])
        if k == "ImplicitCastExpr":
            ck = n.get("castKind")
            if ck in ("LValueToRValue", "NoOp"):
                return self.type16(inner[0])
            if ck == "IntegralCast" and qual in ("int", "unsigned int"):
                return self.type16(inner[0])         # C promotion: transparent
            return ctype(qual)
        if k == "CStyleCastExpr":
            return ctype(qual)
        if k == "UnaryOperator":
            op = n["opcode"]
            if op in ("-", "~", "+"):
                c = self.type16(inner[0])
                if c in LITS:
                    return "L" if op != "~" else c   # still a context-sized constant
                return promote(c)
            if op == "!":
                return "s16"
            if op in ("++", "--"):
                return self.type16(inner[0])
            return ctype(qual)
        if k == "BinaryOperator":
            op = n["opcode"]
            if op in ("<", ">", "<=", ">=", "==", "!=", "&&", "||"):
                return "s16"
            if op in ("<<", ">>"):
                lt = self.type16(inner[0])
                return lt if lt in LITS else promote(lt)
            if op == "=":
                return self.type16(inner[0])
            if op == ",":
                return self.type16(inner[1])
            return usual(self.type16(inner[0]), self.type16(inner[1]))
        if k == "CompoundAssignOperator":
            return self.type16(inner[0])
        if k == "ConditionalOperator":
            return usual(self.type16(inner[1]), self.type16(inner[2]))
        return ctype(qual)

    @staticmethod
    def truncating(parent):
        """Does the (paren-skipped) parent already truncate to 8/16 bits?"""
        if parent is None:
            return False
        k = parent.get("kind")
        q = parent.get("type", {}).get("qualType", "")
        if k == "CStyleCastExpr" and ctype(q) in NARROW:
            return True
        if k == "ImplicitCastExpr" and parent.get("castKind") == "IntegralCast" and ctype(q) in NARROW:
            return True
        return False

    def visit(self, n, parents):
        k = n.get("kind")
        inner = n.get("inner", [])
        # nearest non-paren parent
        p = None
        for anc in reversed(parents):
            if anc.get("kind") != "ParenExpr":
                p = anc
                break
        if k in ("BinaryOperator", "UnaryOperator") and not in_macro(n):
            op = n["opcode"]
            t = self.type16(n)
            if k == "BinaryOperator" and op in ("<", ">", "<=", ">=", "==", "!=", "/", "%"):
                ta, tb = self.type16(inner[0]), self.type16(inner[1])
                if (ta in NARROW or tb in NARROW) and ta in NARROW | LITS and tb in NARROW | LITS \
                        and usual(ta, tb) == "u16":
                    for side, ts in ((inner[0], ta), (inner[1], tb)):
                        # a non-negative literal has the same value either way
                        if promote(ts) == "s16" and is_literal(side) != "pos":
                            self.wrap(side, "(uint16_t)")
                            self.r2 += 1
                            if os.environ.get("WRAP16_LOG"):
                                b, e = span(n)
                                print("  R2:", " ".join(self.src[b:e].split())[:150])
            elif t in ("u16", "s16") and ctype(n.get("type", {}).get("qualType", "")) != "p" \
                    and not all(self.type16(c) in LITS for c in inner if isinstance(c, dict)):
                arith = (k == "BinaryOperator" and op in ("+", "-", "*", "<<")) or \
                        (k == "UnaryOperator" and op in ("-", "~"))
                if k == "BinaryOperator" and op in ("&", "|", "^") and t == "u16":
                    arith = any(promote(self.type16(c)) == "s16" and is_literal(c) != "pos"
                                for c in inner[:2])
                if k == "UnaryOperator" and is_literal(n) == "neg" and t == "s16":
                    arith = False      # -0x69e2 etc. fits in 16 bits already
                if arith and not self.truncating(p):
                    self.wrap(n, "(uint16_t)" if t == "u16" else "(int16_t)")
                    self.r1 += 1
        for c in inner:
            if isinstance(c, dict):
                self.visit(c, parents + [n])

    def apply(self):
        # emit openers outermost-first and closers innermost-first
        events = []
        for b, e, pre in self.edits:
            events.append((b, 1, -(e - b), pre + "("))
            events.append((e, 0, (e - b), ")"))
        events.sort(key=lambda x: (x[0], x[1], x[2]))
        out, pos = [], 0
        for off, _kind, _w, text in events:
            out.append(self.src[pos:off])
            out.append(text)
            pos = off
        out.append(self.src[pos:])
        return "".join(out)


def main(path, extra_flags=()):
    src = open(path).read()
    cmd = ["clang", "-std=gnu11", "-I.", "-Xclang", "-ast-dump=json", "-fsyntax-only",
           "-w", "-Wno-int-conversion", "-Wno-incompatible-pointer-types", *extra_flags, path]
    ast = json.loads(subprocess.run(cmd, capture_output=True, text=True, check=True).stdout)
    p = Pass(src)
    for d in ast.get("inner", []):
        if d.get("kind") == "FunctionDecl" and d.get("name", "").startswith("FUN_1000_") \
                and any(c.get("kind") == "CompoundStmt" for c in d.get("inner", [])):
            p.visit(d, [])
    # drop duplicate edits (the same node reached twice)
    p.edits = sorted(set(p.edits))
    open(path, "w").write(p.apply())
    print("wrap16: %d arithmetic wraps, %d unsigned-compare casts" % (p.r1, p.r2))


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "game.c")
