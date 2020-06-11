# I2CFan
A Digispark ATtiny85-based PWM-Fan controller based on CPU temperature
## How does it work?
I2CFan starts when your pi boots up and runs in the background to send the CPU core temperature via the I2C interface to the µC, which then does all the processing.
This also means that if anyone was going to implement a PID controller, the Pi would have no additional loads.
When the CPU temperature surpasses a certain threshold (Here I chose 40°C), the fan Speed will be raised. When it drops below a certain temperature threshold (I chose 30°C), the fan speed will be lowered. In case you think the temperature goals are not realistic (which they probably are), feel free to make a pull request.

## Will this hurt my RetroPie performance?
FanGPIO is a super small script written in C to avoid any additional stress on your pi. 

## Instructions:
**You need** a Digispark ATtiny85 (or a cheap clone, as I did), and a small 5V fan. Be aware that the voltage regulator on the Digispark can deliver 500 mA maximum current, and most likely need heat sinking above a load of 150 mA. 
In case your Fan is bigger, you could consider using the USB port itself as a power source, but then you either would need to use another port, or solder to the Digispark. Also keep the power limits of your USB port in mind!

### How to install the script:
To install this simple script on your raspberry pi copy and paste the following

```
git clone https://github.com/vguttmann/I2CFan
cd I2CFan
sudo sh install.sh
```

After executing the script, your Pi will automatically reboot, and voilá: You have a temperature controlled Fan!

### How to wire up the Pi:
For my version, I used a Digispark ATtiny85 clone, as they are much cheaper, but they tend to have quite a high "failure rate", meaning they don't work out of the box, but can be fixed via a firmware update (due to manufacturing tolerances, one of my five Digisparks only worked when used with an old 32bit PC on Linux, where I then upgraded the firmware). 
Furthermore you need a fan, for which I chose the Noctua NF-A4x20 5V PWM. Noctua, because their Fans are extremely quiet, 40mm because this fits my case, 20mm because I have the space touse one, and although the 10mm and 20mm version have virtually the same air removal rate, the 20mm fan offers a higher pressure, which is important in cases built for design rather than airflow (such as my NESPi+ case), and I think why I chose the 5V PWM version is obvious.

You have to upload the Arduino code to the Digispark using the Arduino IDE, then plug it into a USB port, attach the PWM cable of the fan (In my case it was blue) to Pin 1, and the power (Yellow, or red, look at the manual) and ground (black) to the 5V and GND pin of the Digispark.
* ATtiny Pin 5 = I2C SDA on DS1621  & GPIO
* ATtiny Pin 7 = I2C SCK on DS1621  & GPIO
