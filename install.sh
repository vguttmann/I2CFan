#!/bin/bash
echo Installing I2CFanController - by bugfish03 - https://github.com/bugfish03
mkdir /home/pi/.I2CFan
cp I2CFan.c /home/pi/.I2CFan/
cd /home/pi/.I2CFan
sh build
cd ..
echo Compiling I2CFan
gcc -Wall -o I2CFan I2CFan.c -l
echo I2CFan Compiled
echo adding I2CFan to systemd service
cp /home/pi/I2CFan/I2CFan.service /etc/systemd/system/I2CFan.service
echo starting I2CFan service
systemctl enable I2CFan.service
rm /home/pi/.I2CFan/I2CFan.c
echo "FINISHED rebooting now for changes to take effect"
reboot