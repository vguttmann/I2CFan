#!/bin/bash
echo Installing I2CFanController - by bugfish03 - https://github.com/bugfish03
mkdir /home/pi/.I2CFan
cp I2C_Fan_Controller.c /home/pi/.I2CFan/
cd /home/pi/.I2CFan
sh build
cd ..
echo Compiling I2C_Fan_Controller.c
gcc -Wall -o I2C_Fan_Controller I2C_Fan_Controller.c
echo I2C_Fan_Controller.c Compiled
echo adding I2C_Fan_Controller.c to systemd service
cp /home/pi/I2CFan/I2C_Fan_Controller.service /etc/systemd/system/I2C_Fan_Controller.service
echo starting I2CFan service
systemctl enable I2C_Fan_Controller.service
rm /home/pi/.I2CFan/I2C_Fan_Controller.c
rm /home/pi/I2CFan
echo "FINISHED rebooting now for changes to take effect"
reboot
