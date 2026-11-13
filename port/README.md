# SkyRoads – native macOS port of the decompilation

This directory builds a native (arm64/x86_64) macOS version of SkyRoads
(Bluemoon, 1993) from the Ghidra pseudo-C in `../build/skyroads.c`.  It is a
*rewrite*, not an emulator: the game logic is the decompiled C, compiled
natively; the parts Ghidra could not express (hand written assembly, BIOS/DOS
calls, hardware access) were re-implemented in C from the disassembly.

The original data files are required (`../resources/Skyroads/*.LZS`, `*.DAT`,
`*.SND`, `DEMO.REC`).

## Build & run

Requirements: Xcode command line tools, Python 3, SDL2 (`brew install sdl2`).

    cd port
    make            # builds ./skyroads
    ./skyroads      # finds ../resources/Skyroads automatically
    make app        # builds SkyRoads.app (data files and SDL bundled inside)

The data directory is searched in: `$SKYROADS_DATA`, the current directory,
`./data`, `./Skyroads`, `resources/Skyroads`, `../resources/Skyroads`, and the
same paths relative to the executable / app `Resources` folder.

Controls are the original ones: arrows to steer/accelerate/brake, Space to jump,
Esc to go back, Enter to select.  A game controller is mapped to the arrow keys,
A = jump, Start = Enter, B = Esc; the in-game *joystick* and *mouse* control
modes also work.  Alt/Cmd+Enter toggles full screen, Cmd+Q quits.
Progress (`skyroads.cfg`) is stored in
`~/Library/Application Support/SkyRoads/SkyRoads/`.

## How it works

| file | contents |
|------|----------|
| `transform.py` | turns `../build/skyroads.c` into `game.c`/`game.h` (types, DS memory accesses, K&R definitions, real stack frames, call-site fixups) |
| `game.c` | generated game logic (~80 functions) |
| `manual.c` | blitters, timer/keyboard hooks and other routines whose decompilation lost segment registers |
| `render.c` | the road/ship renderer (hand written assembly at 1000:2cce–3acb) and its per-frame driver |
| `runtime.c` | DOS file/memory services, LZS decompressor, data loaders, C runtime helpers |
| `audio.c` | AdLib music player port + OPL2 FM synth, Sound Blaster PCM, PC speaker |
| `hw.c` | timer interrupt (180 Hz), keyboard interrupt, vsync, mouse/joystick |
| `video.c` | VGA register model, 8×8 font glyph drawing |
| `platform.c`, `main.c` | SDL window/audio/input, file access, threads |

Memory model: the program's 16-bit address space is kept as a flat 1 MiB
array (`g_mem`) with the unpacked EXE image loaded at `1000:0000`; the data
segment is `1676:0000`.  The data segment is 64 KiB aligned in host memory and
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
`SKY_WARP=n` (jump to n rows before the end of the road), `SKY_WAV=file`
(raw audio dump).  `run_test.sh` and `check_arity.py` are development aids.

## Limitations

* Only the VGA (mode 13h) code paths are supported; the EGA renderer is not ported.
* The OPL2 synthesizer is an approximation of the YM3812, not a cycle-exact core.
