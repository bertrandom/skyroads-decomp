#!/bin/bash
# usage: run_test.sh "shot times ms" ["keys"] [timeout]
rm -rf /tmp/shots; mkdir -p /tmp/shots shots view; rm -f shots/*
SKY_SHOT=/tmp/shots SKY_SHOT_AT="$1" SKY_KEYS="$2" timeout ${3:-10} ./skyroads > /tmp/sky.out 2>&1
echo "rc=$?"
for f in /tmp/shots/*.bmp; do [ -e "$f" ] && sips -s format png -z 400 640 "$f" --out shots/$(basename "$f" .bmp).png >/dev/null; done
ls shots
magick /tmp/shots/*.bmp -filter point -resize 200% +append -resize 50% shots/sheet.png 2>/dev/null; magick shots/sheet.png -crop 1280x400 +repage shots/row_%d.png 2>/dev/null
