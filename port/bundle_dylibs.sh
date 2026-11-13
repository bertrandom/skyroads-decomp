#!/bin/sh
# Copy non-system dylibs (SDL2 / sdl2-compat / SDL3) into the app bundle and
# rewrite their install names so the app runs on machines without Homebrew.
APP="$1"
BIN="$APP/Contents/MacOS/SkyRoads"
FW="$APP/Contents/Frameworks"
copy_deps() {
    otool -L "$1" | awk 'NR>1 {print $1}' | grep -E '^/(opt|usr/local)/' | while read -r lib; do
        name=$(basename "$lib")
        if [ ! -f "$FW/$name" ]; then
            cp -L "$lib" "$FW/$name"
            chmod u+w "$FW/$name"
            install_name_tool -id "@rpath/$name" "$FW/$name"
            copy_deps "$FW/$name"
        fi
        install_name_tool -change "$lib" "@rpath/$name" "$1"
    done
}
copy_deps "$BIN"
# sdl2-compat dlopen()s SDL3 as @loader_path/libSDL3.dylib
for f in /opt/homebrew/lib/libSDL3.dylib /usr/local/lib/libSDL3.dylib; do
    if [ -f "$f" ] && [ ! -f "$FW/libSDL3.dylib" ]; then
        cp -L "$f" "$FW/libSDL3.dylib"; chmod u+w "$FW/libSDL3.dylib"
        install_name_tool -id "@rpath/libSDL3.dylib" "$FW/libSDL3.dylib" 2>/dev/null
    fi
done
install_name_tool -add_rpath "@executable_path/../Frameworks" "$BIN" 2>/dev/null || true
