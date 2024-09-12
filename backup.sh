#!/bin/bash
cd ~/Documents/cs334
cp /home/student334/.bashrc ~/Documents/cs334/raspberrypi
hostname -I > ~/Documents/cs334/raspberrypi/ip.md
pwd

git add ~/Documents/cs334/backup.sh
git add ~/Documents/cs334/raspberrypi/ip.md
git add ~/Documents/cs334/raspberrypi/.bashrc

git commit -m "backed up some files"
git push
