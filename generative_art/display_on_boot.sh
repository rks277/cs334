#!/bin/bash

cd ~/Documents/cs334/generative_art/src
python -m http.server 7002 &
sleep 3
chromium-browser --new-window http://localhost:7000