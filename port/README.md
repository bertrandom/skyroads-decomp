# SkyRoads – native macOS port of the decompilation

This directory builds a native (arm64/x86_64) macOS version of SkyRoads
(Bluemoon, 1993) from the Ghidra pseudo-C in `../build/skyroads_bluemoon.c`.
It is a *rewrite*, not an emulator: the game logic is the decompiled C,
compiled natively; the parts Ghidra could not express (hand written assembly,
BIOS/DOS calls, hardware access) were re-implemented in C from the disassembly.

The game files are Bluemoon's current release (`../resources/Skyroads`, from
`../resources/SkyRoads (Bluemoon).zip`; its `SKYROADS.EXE` is the same file as
SkyRoads Xmas Special's `SKYXMAS.EXE`): 14-song music with a menu theme, the
newer intro credits and help pages, and the burning row on Asteroid Belt
Road 1. The port was first made from an earlier, DIET-packed release
(`../resources/SkyRoads (1993).zip`, decompiled in `../build/skyroads.c`) and
then moved onto this one: `../scripts/addrmap.py` aligns the two builds
instruction by instruction and writes `../build/addrmap.json` (where every
function and data address moved), and `../scripts/rebase_port.py` rewrote the
hand-written code with it.

## Build & run

Requirements: Xcode command line tools, Python 3, SDL2 (`brew install sdl2`).

    cd port
    make            # builds ./skyroads
    ./skyroads      # finds ../resources/Skyroads automatically
    make app        # builds SkyRoads.app (data files and SDL bundled inside)
    make test       # replays the attract demo, see below

The data directory is searched in: `$SKYROADS_DATA`, the current directory,
`./data`, `./Skyroads`, `resources/Skyroads`, `../resources/Skyroads`, and the
same paths relative to the executable / app `Resources` folder.

Controls are the original ones: arrows to steer/accelerate/brake, Space to jump,
Esc to go back, Enter to select.  A game controller is mapped to the arrow keys,
A = jump, Start = Enter, B = Esc; the in-game *joystick* and *mouse* control
modes also work.  Alt/Cmd+Enter toggles full screen, W widescreen (also
Cmd/Alt+W), S the sound (the game's own setting, saved), Cmd+Q quits.
Progress (`skyroads.cfg`) is stored in
`~/Library/Application Support/SkyRoads/SkyRoads/`.

## Test

`make test` runs the game with `SKY_DEMO_TEST=1`: it waits through the intro
for the attract demo, which replays `DEMO.REC` (input recorded by road
position), and exits 0 when the ship reaches the finish row of the demo road,
1 if it is lost on the way (crash, burn, fall, fuel, oxygen), 2 if the demo
does not finish within 150 s. The recorded input only gets the ship there if
the physics and collision code behave exactly like the original, so this
checks the decompiled code together with the hand-written runtime (about 85 s,
real time; it opens a window).

## How it works

| file | contents |
|------|----------|
| `transform.py` | turns `../build/skyroads.c` into `game.c`/`game.h` (types, DS memory accesses, K&R definitions, real stack frames, call-site fixups, argument-count normalisation logged to `arity.log`) |
| `gen_protos.py` | writes `protos.h`: one full prototype per function, derived from the definitions |
| `wrap16.py` | restores 16-bit integer semantics in `game.c` using Clang's typed AST: 16-bit arithmetic is truncated where 32-bit C would not wrap, mixed-sign comparisons become unsigned |
| `game.c` | generated game logic (~80 functions) |
| `manual.c` | blitters, timer/keyboard hooks and other routines whose decompilation lost segment registers |
| `render.c` | the road/ship renderer (hand written assembly at 1000:2cce–3acb) and its per-frame driver |
| `runtime.c` | DOS file/memory services, LZS decompressor, data loaders, C runtime helpers |
| `audio.c` | AdLib music player port, Sound Blaster PCM, PC speaker; the AdLib chip itself is [Nuked-OPL3](https://github.com/nukeykt/Nuked-OPL3) 1.8 (`thirdparty/nuked-opl3`, LGPL-2.1) |
| `hw.c` | timer interrupt (180 Hz), keyboard interrupt, vsync, mouse/joystick |
| `ghost.c` | ghost racers: records each run and replays earlier runs of the same road as translucent ships, or in the web build the live runs of other players through `../server/relay.py` (on by default in the web build, `SKY_GHOSTS=1` natively) |
| `video.c` | VGA register model, 8×8 font glyph drawing |
| `platform.c`, `main.c` | SDL window/audio/input, file access, threads |

Memory model: the program's 16-bit address space is kept as a flat 1 MiB
array (`g_mem`) with the EXE's load image at `1000:0000`; the data segment is
`166e:0000`.  The data segment is 64 KiB aligned in host memory and
the generated functions' stack frames are allocated inside it (as in the
original, SS == DS), so near pointers and 16-bit offsets are interchangeable.
Far pointers / segments are used as-is (`seg << 4` into `g_mem`).

Threads mirror the PC: the game code runs on its own thread, a timer thread
fires the original's 180 Hz INT 8 handler (game clock, music, speaker), and the
main thread presents the mode 13h framebuffer and delivers keyboard input
through the original INT 9 handler logic.

Debug helpers (environment variables): `SKY_DEBUG=1` (file/alloc tracing),
`SKY_SHOT=dir SKY_SHOT_AT=ms,ms…` (BMP screenshots), `SKY_KEYS=ms:scancode[:hold]…`
(scripted input), `SKY_AUTOKEYS=0d,4800,…` (keys for blocking menu reads),
`SKY_WARP=n` (jump to n rows before the end of the road), `SKY_ROAD=n`
(skip the intro and menus and start road n, 1-30), `SKY_FLY=1` (the ship
flies over everything in the middle lane and cannot crash, fall or run out:
hold accelerate to go through a whole road), `SKY_WAV=file`
(raw audio dump).  Widescreen: `SKY_WIDE=1` (or Cmd/Alt+W), `SKY_VIEW_W=n`
(force the view to n columns, up to 573), `SKY_WIDE_FULL=1` / `SKY_WIDE_DIFF=1`
(draw the margin road's model over the frame on alternate lines / mark where
it differs).  `run_test.sh` and `check_arity.py` are development aids.

A WebAssembly build of the same code lives in `../web` (see its README).

## Limitations

* Only the VGA (mode 13h) code paths are supported; the EGA renderer is not ported.

## Third-party code

`thirdparty/nuked-opl3` is Nuked-OPL3 by Nuke.YKT (upstream commit
`765ec96`), licensed under the GNU LGPL 2.1 or later (its `LICENSE`); it is
compiled unmodified into the native and web builds.

