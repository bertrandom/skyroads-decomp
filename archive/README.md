# The first decompilation (1993 release)

The port was first decompiled from an earlier release of SkyRoads
(`../resources/SkyRoads (1993).zip`), whose `SKYROADS.EXE` is packed with
DIET, and was then moved onto Bluemoon's current release, which it builds
from now (`../ghidra/`). Nothing here is used by the build; it is kept to
show how the port got where it is.

| | |
|---|---|
| `undiet.py` | unpacks the DIET-packed EXE: `SKYROADS_unpacked.EXE` |
| `ghidra_1993/` | the Ghidra project of the unpacked EXE |
| `skyroads_1993.c` | its pseudo-C, exported with `../ghidra/ExportDecompiled.java`, which the port was first transformed from |
| `addrmap.py` | aligns the two builds instruction by instruction and writes `addrmap.json`: where every function and data address moved |
| `rebase_port.py` | rewrote the hand-written code in `../port` with that map (`--write`) |
