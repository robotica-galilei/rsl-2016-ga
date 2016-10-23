#include <Wire.h>
#include "SoftI2CMaster.h"

byte i2cWriteBuffer[10];
byte i2cReadBuffer[10];

byte i2cWriteBuffer2[10];
byte i2cReadBuffer2[10];

SoftI2CMaster i2c = SoftI2CMaster( sdaPin,sclPin );
SoftI2CMaster i2c2 = SoftI2CMaster( sdaPin2,sclPin2 );


#define SensorAddressWrite 0x29 //
#define SensorAddressRead 0x29 //
#define EnableAddress 0xa0 // register address + command bits

#define ATimeAddress 0xa1 //(suo standard)
#define WTimeAddress 0xa3 // register address + command bits
#define ConfigAddress 0xad // register address + command bits
#define ControlAddress 0xaf // register address + command bits
#define IDAddress 0xb2 // register address + command bits
#define ColorAddress 0xb4 // register address + command bits


void Writei2cRegisters(byte numberbytes, byte command)
{
  byte i = 0;

  i2c.beginTransmission(SensorAddressWrite);   // Send address with Write bit set
  i2c.write(command);                       // Send command, normally the register address
  for (i=0;i<numberbytes;i++)                     // Send data
    i2c.write(i2cWriteBuffer[i]);
  i2c.endTransmission();

  delayMicroseconds(100);   // allow some time for bus to settle    
}

void Writei2cRegisters2(byte numberbytes, byte command)
{
  byte i = 0;

  i2c2.beginTransmission(SensorAddressWrite);   // Send address with Write bit set
  i2c2.write(command);                        // Send command, normally the register address
  for (i=0;i<numberbytes;i++)                     // Send data
    i2c2.write(i2cWriteBuffer2[i]);
  i2c2.endTransmission();

  delayMicroseconds(100);   // allow some time for bus to settle    
}


byte Readi2cRegisters(int numberbytes, byte command)
{
   byte i = 0;

  i2c.beginTransmission(SensorAddressWrite);   // Write address of read to sensor
  i2c.write(command);
  i2c.endTransmission();

  delayMicroseconds(100);   // allow some time for bus to settle    

   i2c.requestFrom(SensorAddressRead);   // read data
  for(i=0;i<8;i++)
    i2cReadBuffer[i] = i2c.read(SensorAddressRead);
    i2cReadBuffer[i+1] = i2c.readLast();
  i2c.endTransmission();

  delayMicroseconds(100);   // allow some time for bus to settle    
}

byte Readi2cRegisters2(int numberbytes, byte command)
{
   byte i = 0;

  i2c2.beginTransmission(SensorAddressWrite);   // Write address of read to sensor
  i2c2.write(command);
  i2c2.endTransmission();

  delayMicroseconds(100);   // allow some time for bus to settle    

   i2c2.requestFrom(SensorAddressRead);   // read data
  for(i=0;i<8;i++)
    i2cReadBuffer2[i] = i2c2.read(SensorAddressRead);
    i2cReadBuffer2[i+1] = i2c2.readLast();
  i2c2.endTransmission();

  delayMicroseconds(100);   // allow some time for bus to settle    
}



void init_TCS34725(void)
{
  i2cWriteBuffer[0] = 0x10;
  Writei2cRegisters(1,ATimeAddress);  // RGBC timing is 256 - contents x 2.4mS =
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1,ConfigAddress);   // Can be used to change the wait time
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1,ControlAddress);  // RGBC gain control
  i2cWriteBuffer[0] = 0x03;
  Writei2cRegisters(1,EnableAddress); // enable ADs and oscillator for sensor
}
void init_TCS347252(void)
{
  i2cWriteBuffer2[0] = 0x10;
  Writei2cRegisters2(1,ATimeAddress); // RGBC timing is 256 - contents x 2.4mS =
  i2cWriteBuffer2[0] = 0x00;
  Writei2cRegisters2(1,ConfigAddress);   // Can be used to change the wait time
  i2cWriteBuffer2[0] = 0x00;
  Writei2cRegisters2(1,ControlAddress);  // RGBC gain control
  i2cWriteBuffer2[0] = 0x03;
  Writei2cRegisters2(1,EnableAddress);  // enable ADs and oscillator for sensor
}/*


Reads the register values for clear, red, green, and blue.
*/
void get_Colors(void)     //sinistra
{
  unsigned int clear_color = 0;
  unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;

  Readi2cRegisters(8,ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer[1]<<8) + (unsigned int)i2cReadBuffer[0];
  red_color = (unsigned int)(i2cReadBuffer[3]<<8) + (unsigned int)i2cReadBuffer[2];
  green_color = (unsigned int)(i2cReadBuffer[5]<<8) + (unsigned int)i2cReadBuffer[4];
  blue_color = (unsigned int)(i2cReadBuffer[7]<<8) + (unsigned int)i2cReadBuffer[6];
 
  if (green_color> (clear_color * costanteverde1))
  {
    verde1=true;
    Serial.print("sinistra: ");
    Serial.println(green_color);
  }

}

void get_Colors2(void)      //destra
{
  unsigned int clear_color = 0;
  unsigned int red_color = 0;
  unsigned int green_color = 0;
  unsigned int blue_color = 0;

  Readi2cRegisters2(8,ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer2[1]<<8) + (unsigned int)i2cReadBuffer2[0];
  red_color = (unsigned int)(i2cReadBuffer2[3]<<8) + (unsigned int)i2cReadBuffer2[2];
  green_color = (unsigned int)(i2cReadBuffer2[5]<<8) + (unsigned int)i2cReadBuffer2[4];
  blue_color = (unsigned int)(i2cReadBuffer2[7]<<8) + (unsigned int)i2cReadBuffer2[6];

  if (green_color> (clear_color * costanteverde2))
  {
    verde2=true;
    Serial.print("destra: ");
    Serial.println(green_color);
  }

}

