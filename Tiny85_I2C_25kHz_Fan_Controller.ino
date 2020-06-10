/* ATtiny85 as an I2C Slave            BroHogan                           1/12/11
 * Example of ATtiny I2C slave receiving and sending data to an Arduino master.
 * Gets data from master, adds 10 to it and sends it back.
 * SETUP:
 * ATtiny Pin 1 = (RESET) N/U                      ATtiny Pin 2 = (D3) N/U
 * ATtiny Pin 3 = (D4) to LED1                     ATtiny Pin 4 = GND
 * ATtiny Pin 5 = I2C SDA on DS1621  & GPIO        ATtiny Pin 6 = (D1) to LED2
 * ATtiny Pin 7 = I2C SCK on DS1621  & GPIO        ATtiny Pin 8 = VCC (2.7-5.5V)
 * NOTE! - It's very important to use pullups on the SDA & SCL lines!
 * Current Rx & Tx buffers set at 32 bytes - see usiTwiSlave.h
 * Credit and thanks to Don Blake for his usiTwiSlave code. 
 * More on TinyWireS usage - see TinyWireS.h
 */

#include "TinyWireS.h" // wrapper class for I2C slave routines

#define I2C_SL_ADDR 0x26 // i2c slave address (38)
#define PWM_PIN 1        // ATtiny Pin 6

int coreTemp = 35;
int lowerLimit = 30;
int upperLimit = 40;

class FanController
{
public:
  void raiseSpeed();
  void lowerSpeed();

  FanController();

  FanController::raiseSpeed()
  {
    if (!(OCR0B > 80))
    {
      OCR0B += 2;
    }
  }

  FanController::lowerSpeed()
  {
    if (!(OCR0B < 16))
    {
      OCR0B--;
    }
  }
}

void setup()
{
  pinMode(PWM_PIN, OUTPUT);
  TCCR0A = _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
  TCCR0B = _BV(WGM02) | _BV(CS01);
  OCR0A = 82;
  TinyWireS.begin(); // init I2C Slave mode
  OCR0B = 16;
  FanController();
}

void loop()
{
  if (TinyWireS.available())
  {
    coreTemp = (int)TinyWireS.receive();
    if (coreTemp > upperLimit)
    {
      FanController.raiseSpeed();
    }
    else if (coreTemp < lowerLimit)
    {
      FanController.lowerSpeed();
    }
  }
}
