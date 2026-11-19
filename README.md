# SkyRoads decompilation

SkyRoads (Bluemoon Interactive, 1993) decompiled from its DOS executable
into C that builds and runs natively. It is not an emulator: the game's own
logic, exported from Ghidra and transformed into compilable C, runs as a
native program, with the parts Ghidra could not express (hand-written
assembly, BIOS and DOS calls, hardware access) re-implemented from the
disassembly. The attract demo replays to the end of its road exactly as on
the original (`make -C port test`).

## Layout

| | |
|---|---|
| `ghidra/` | the Ghidra project of `SKYROADS.EXE` (`project/`), its pseudo-C (`skyroads_bluemoon.c`) and the script that exports it (`ExportDecompiled.java`) |
| `port/` | the game in C and the native macOS build (see `port/README.md`): the generated `game.c` and the hand-written code beside it; `port/gen/` the generators, `port/sdl/` the platform layer (window, sound, input, files, on SDL2) |
| `resources/` | the game: Bluemoon's current release unpacked in `Skyroads/` (what every build uses), and the original zips of it, the 1993 release and the Xmas Special |
| `art/` | pictures exported from the game's data: the road backdrops and menu screens on wider frames, painted out for the widescreen margins (`filled/`), and the control panel |
| `archive/` | the first decompilation, of the 1993 release, and the tools that moved the port onto the current one; not used by the build (see `archive/README.md`) |

## From the executable to the game

    resources/Skyroads/SKYROADS.EXE
      → Ghidra (ghidra/project), exported by ghidra/ExportDecompiled.java
      → ghidra/skyroads_bluemoon.c       the pseudo-C
      → port/gen/transform.py            types, memory accesses, stack frames, 16-bit arithmetic
      → port/game.c, game.h, protos.h    generated, not committed
      + port/*.c                         the hand-written rest: runtime, renderer, music, ...
      + port/sdl/*.c                     the platform layer
      → port/skyroads                    the native build (make -C port)

## Builds of it elsewhere

Two other repositories build this code, each with this repository as a git
submodule in `decomp/`:

- **skyroads-web**: the browser version (Emscripten), played at
  <https://skyroads.org>, with live ghosts of other players and its deploy.
  It shares `port/sdl/` with the native build.
- **skyroads-pocket**: an openFPGA core for the Analogue Pocket, which runs
  the game code on a RISC-V CPU in the FPGA, with its own platform layer
  (firmware and hardware) in place of `port/sdl/`.

A change here reaches them when their submodule is moved to the new commit.

SkyRoads is © 1993 Bluemoon Interactive, who have made it freeware:
<http://www.bluemoon.ee/history/skyroads/index.html>.
