# Native macOS build of the SkyRoads decompilation.
#
#   make            build ./skyroads (run it from the repository; it finds
#                   ../resources/Skyroads automatically)
#   make app        build SkyRoads.app (self-contained: data + SDL2 inside)
#   make regen      re-run the transformation of ../build/skyroads.c
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

OBJS = main.o runtime.o video.o platform.o hw.o audio.o manual.o render.o game.o
DATA = ../resources/Skyroads
APP  = SkyRoads.app

all: skyroads

MANUAL_SRC = runtime.c manual.c render.c audio.c hw.c video.c

game.c game.h protos.h: ../build/skyroads.c transform.py gen_protos.py $(MANUAL_SRC)
	python3 transform.py

regen:
	python3 transform.py

image_data.h: ../build/SKYROADS_unpacked.EXE gen_image.py
	python3 gen_image.py ../build/SKYROADS_unpacked.EXE image_data.h

%.o: %.c compat.h protos.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

game.o: game.c game.h compat.h protos.h
main.o: main.c image_data.h compat.h
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
	rm -f $(OBJS) skyroads game.c game.h protos.h image_data.h arity.log
	rm -rf $(APP)

.PHONY: all app clean regen
