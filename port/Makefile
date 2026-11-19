# Native macOS build of the SkyRoads decompilation.
#
#   make            build ./skyroads (run it from the repository; it finds
#                   ../resources/Skyroads automatically)
#   make app        build SkyRoads.app (self-contained: data + SDL2 inside)
#   make regen      re-run the transformation of ../ghidra/skyroads_bluemoon.c
#   make songs      the game's songs as WAV files in songs/, as this build
#                   plays them (tools/render_songs.c)
#   make clean
CC      ?= cc
SDL_CFLAGS := $(shell pkg-config --cflags sdl2 2>/dev/null || echo -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE)
SDL_LIBS   := $(shell pkg-config --libs sdl2 2>/dev/null || echo -L/opt/homebrew/lib -lSDL2)

CFLAGS  ?= -O2 -g
CFLAGS  += -std=gnu11 -I. -fno-strict-aliasing -fwrapv -Wall \
           -Wno-int-conversion -Wno-incompatible-pointer-types -Wno-parentheses \
           -Wno-pointer-sign -Wno-unused-variable -Wno-unused-but-set-variable \
           -Wno-unused-function -Wno-missing-braces -Wno-constant-conversion \
           -Wno-shift-count-overflow -Wno-return-type -Wno-deprecated-non-prototype \
           -Wno-implicit-int -Wno-unused-label -Wno-int-to-pointer-cast \
           -Wno-pointer-to-int-cast -Wno-incompatible-function-pointer-types \
           -Wno-tautological-constant-out-of-range-compare -Wno-dangling-else \
           -Wno-unused-value -Wno-sometimes-uninitialized -Wno-uninitialized \
           -Wno-incompatible-pointer-types-discards-qualifiers -Wno-strict-prototypes

# the SDL platform layer (sdl/): main.c, platform.c, hw.c, audio.c
vpath %.c sdl
OBJS = main.o runtime.o video.o platform.o hw.o audio.o music.o manual.o render.o game.o ghost.o sign.o opl3.o
DATA = ../resources/Skyroads
APP  = SkyRoads.app

all: skyroads

MANUAL_SRC = runtime.c manual.c render.c sdl/audio.c music.c sdl/hw.c video.c

# the generators (gen/) run from here: their paths are relative to port/
game.c game.h protos.h: ../ghidra/skyroads_bluemoon.c gen/transform.py gen/gen_protos.py gen/wrap16.py $(MANUAL_SRC)
	python3 gen/transform.py

regen:
	python3 gen/transform.py

image_data.h: ../resources/Skyroads/SKYROADS.EXE gen/gen_image.py
	python3 gen/gen_image.py ../resources/Skyroads/SKYROADS.EXE image_data.h

# widescreen margins painted for each road (../art/backgrounds-ultrawide/filled)
WIDE_BG_DIR = ../art/backgrounds-ultrawide/filled
WIDE_PANEL = ../art/control-panel/control-panel_wide.png
WIDE_MENU_DIR = ../art/menu-backgrounds/4x3/filled
WIDE_INPUTS = gen/gen_wide_bg.py $(wildcard $(WIDE_BG_DIR)/*.png) $(wildcard $(WIDE_PANEL)) $(wildcard $(WIDE_MENU_DIR)/*.png)
# by content, not date: a picture saved with an older date is still noticed
wide_bg.sum: FORCE
	@python3 -c 'import hashlib,sys; print("\n".join(f + " " + hashlib.sha1(open(f, "rb").read()).hexdigest() for f in sys.argv[1:]))' $(WIDE_INPUTS) > $@.new
	@cmp -s $@.new $@ && rm $@.new || mv $@.new $@
wide_bg.h: wide_bg.sum
	python3 gen/gen_wide_bg.py $(WIDE_BG_DIR) wide_bg.h $(WIDE_PANEL) $(WIDE_MENU_DIR)
FORCE:
platform.o: sdl/platform.c wide_bg.h compat.h

%.o: %.c compat.h protos.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

game.o: game.c game.h compat.h protos.h
# Nuked-OPL3 (LGPL-2.1), the AdLib chip emulator
opl3.o: thirdparty/nuked-opl3/opl3.c thirdparty/nuked-opl3/opl3.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: sdl/main.c image_data.h compat.h
runtime.o: runtime.c font8x8.h compat.h

skyroads: $(OBJS)
	$(CC) $(OBJS) $(SDL_LIBS) -o skyroads

app: skyroads
	rm -rf $(APP)
	mkdir -p $(APP)/Contents/MacOS $(APP)/Contents/Resources/data $(APP)/Contents/Frameworks
	cp skyroads $(APP)/Contents/MacOS/SkyRoads
	cp Info.plist $(APP)/Contents/Info.plist
	cp $(DATA)/*.LZS $(DATA)/*.DAT $(DATA)/*.SND $(DATA)/*.REC $(APP)/Contents/Resources/data/
	sh bundle_dylibs.sh $(APP)
	codesign --force --deep -s - $(APP) 2>/dev/null || true
	@echo "built $(APP)"

clean:
	rm -f $(OBJS) skyroads game.c game.h protos.h image_data.h wide_bg.h wide_bg.sum arity.log
	rm -rf $(APP)

.PHONY: test all app clean regen

# Replay the attract demo (DEMO.REC) and check it finishes the demo road:
# the recorded input only gets there if the decompiled physics and the
# hand-written runtime behave exactly like the original.
test: skyroads
	SKY_DEMO_TEST=1 ./skyroads

# the songs as WAV files, through the same player and OPL emulation
render_songs: tools/render_songs.c music.c thirdparty/nuked-opl3/opl3.c image_data.h compat.h protos.h
	$(CC) $(CFLAGS) -o $@ tools/render_songs.c music.c thirdparty/nuked-opl3/opl3.c -lm
songs: render_songs
	mkdir -p songs
	./render_songs $(DATA)/MUZAX.LZS songs
.PHONY: songs
