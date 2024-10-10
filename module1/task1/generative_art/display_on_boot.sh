#!/bin/bash
cd ~/Documents/cs334/generative_art/src
python -m http.server 7000 &
sleep 2

#chromium-browser --new-window http://localhost:7000
#chromium-browser --new-window http://localhost:7002
/usr/bin/chromium-browser --start-fullscreen --disable-gpu http://localhost:7000
