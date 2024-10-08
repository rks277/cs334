#!/bin/bash
cd ~/Documents/cs334
cp /home/student334/.bashrc ~/Documents/cs334/raspberrypi
cp /etc/systemd/system/thanks_koray_for_helping_us_with_this.service ~/Documents/cs334/raspberrypi

cp /boot/config.txt ~/Documents/cs334/raspberrypi/configs/backup_old_config.txt
cp /boot/firmware/config.txt ~/Documents/cs334/raspberrypi/configs/backup_config.txt
cp ~/.config/wayfire.ini ~/Documents/cs334/generative_art
hostname -I > ~/Documents/cs334/raspberrypi/ip.md
pwd

git add -A
# git add ~/Documents/cs334/backup.sh
# git add ~/Documents/cs334/raspberrypi/ip.md
# git add ~/Documents/cs334/raspberrypi/.bashrc

git commit -m "[$(date '+%Y-%m-%d %H:%M:%S')] backed up some files"
git push
