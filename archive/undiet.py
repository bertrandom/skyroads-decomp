"""Unpack a DIET-compressed MZ by emulating the stub to the original entry point.
Runs twice at different load segments; words that differ by the segment delta are relocations."""
import sys, struct
from unicorn import *
from unicorn.x86_const import *

data = open(sys.argv[1], 'rb').read()
out_path = sys.argv[2]

(magic, cblp, cp, crlc, cparhdr, minalloc, maxalloc, ss, sp, csum, ip, cs, lfarlc, ovno) = struct.unpack('<14H', data[:28])
size = cp * 512 - (512 - cblp if cblp else 0)
image = data[cparhdr * 16:size]


def run(psp):
    load = psp + 0x10
    mu = Uc(UC_ARCH_X86, UC_MODE_16)
    mu.mem_map(0, 0x110000)
    mu.mem_write(load * 16, image)
    for i in range(crlc):
        o, s = struct.unpack('<HH', data[lfarlc + i * 4: lfarlc + i * 4 + 4])
        a = (load + s) * 16 + o
        v = struct.unpack('<H', mu.mem_read(a, 2))[0]
        mu.mem_write(a, struct.pack('<H', (v + load) & 0xffff))
    mu.mem_write(psp * 16, b'\xcd\x20' + struct.pack('<H', 0x9000))
    for r, v in ((UC_X86_REG_DS, psp), (UC_X86_REG_ES, psp), (UC_X86_REG_SS, load + ss),
                 (UC_X86_REG_SP, sp), (UC_X86_REG_CS, load + cs), (UC_X86_REG_IP, ip)):
        mu.reg_write(r, v)
    st = {'stub': None, 'oep': None}

    def on_code(uc, addr, sz, _):
        c = uc.reg_read(UC_X86_REG_CS)
        if st['stub'] is None and c != load + cs:
            st['stub'] = c  # stub relocated itself high
        elif st['stub'] is not None and c != st['stub']:
            st['oep'] = (c, uc.reg_read(UC_X86_REG_IP), uc.reg_read(UC_X86_REG_SS), uc.reg_read(UC_X86_REG_SP))
            uc.emu_stop()

    mu.hook_add(UC_HOOK_CODE, on_code)
    mu.emu_start((load + cs) * 16 + ip, 0x110000, count=50_000_000)
    c, i, s, p = st['oep']
    end = st['stub'] * 16  # decompressed program lives below the relocated stub
    dump = bytes(mu.mem_read(load * 16, end - load * 16))
    return load, dump, (c - load, i, s - load, p)


A, B = 0x1000, 0x2000
la, da, ea = run(A)
lb, db, eb = run(B)
assert ea == eb, (ea, eb)
n = min(len(da), len(db))
da, db = da[:n], db[:n]
delta = lb - la

relocs = []
fixed = bytearray(da)
i = 0
while i < n - 1:
    wa = struct.unpack_from('<H', da, i)[0]
    wb = struct.unpack_from('<H', db, i)[0]
    if wa != wb:
        assert (wb - wa) & 0xffff == delta, hex(i)
        struct.pack_into('<H', fixed, i, (wa - la) & 0xffff)
        relocs.append(i)
        i += 2
    else:
        i += 1

# trim trailing zeros (BSS) -> extra paragraphs go to minalloc
body = bytes(fixed).rstrip(b'\0')
body += b'\0' * (-len(body) % 16)
bss_paras = (n - len(body)) // 16

hdr_len = 0x20 + 4 * len(relocs)
hdr_len += -hdr_len % 512
total = hdr_len + len(body)
oc, oi, os_, op = ea
hdr = struct.pack('<14H', 0x5A4D, total % 512, (total + 511) // 512, len(relocs), hdr_len // 16,
                  bss_paras + minalloc, 0xFFFF, os_ & 0xffff, op, 0, oi, oc & 0xffff, 0x20, 0)
hdr += b'\0' * 4
for r in relocs:
    hdr += struct.pack('<HH', (r >> 4) & 0xF000, r & 0xFFFF) if False else struct.pack('<HH', r & 0xF, r >> 4)
hdr += b'\0' * (hdr_len - len(hdr))
open(out_path, 'wb').write(hdr + body)
print(f'entry {oc:04x}:{oi:04x} stack {os_:04x}:{op:04x} relocs {len(relocs)} image {len(body):#x} bss paras {bss_paras:#x}')
