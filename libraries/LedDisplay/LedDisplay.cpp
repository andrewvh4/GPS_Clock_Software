#include "LedDisplay.h"

#include "DateTime.h"
#include "RTClib.h"
#include "LedControl_modified.h"
#include <Arduino.h>

byte flipByte(byte c)
{
  c = ((c>>1)&0x55)|((c<<1)&0xAA);
  c = ((c>>2)&0x33)|((c<<2)&0xCC);
  c = (c>>4) | (c<<4) ;

  return c;
}

//////////////////////////////////////////////////////////////////////////////////
BinaryDisplay::BinaryDisplay(int dataPin, int clkPin, int csPin, int numDevices=1)
{
  LedControl temp(dataPin, clkPin, csPin, numDevices);
  LedControlBinary = temp;
  LedControlBinary.shutdown(0, false);
  LedControlBinary.clearDisplay(0);
}

void BinaryDisplay::write(DateTime DateTime)
{
  LedControlBinary.setRow(0, 0, flipByte((int8_t) DateTime.year() -2000   )>>1);
  LedControlBinary.setRow(0, 1, flipByte((int8_t) DateTime.month()        )>>1);
  LedControlBinary.setRow(0, 2, flipByte((int8_t) DateTime.day()          )>>1);
  LedControlBinary.setRow(0, 3, flipByte((int8_t) DateTime.weekOfTheYear())>>1);
  LedControlBinary.setRow(0, 4, flipByte((int8_t) DateTime.dayOfTheWeek() )>>1);
  LedControlBinary.setRow(0, 5, flipByte((int8_t) DateTime.hour()         )>>1);
  LedControlBinary.setRow(0, 6, flipByte((int8_t) DateTime.minute()       )>>1);
  LedControlBinary.setRow(0, 7, flipByte((int8_t) DateTime.second()       )>>1);
  LedControlBinary.setIntensity(0, intensity);
}

void BinaryDisplay::setIntensity(int intens)
{
  intensity = intens;
  LedControlBinary.setIntensity(0, intens);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
ConventionalDisplay::ConventionalDisplay(int dataPin, int clkPin, int csPin, int numDevices=4)
{
  LedControl temp(dataPin, clkPin, csPin, numDevices);
  LedControlConventional = temp;
  for(int i = 0; i<4; i++)
  {
    LedControlConventional.shutdown(i, false);
  }
  LedControlConventional.clearDisplay(0);
}

void ConventionalDisplay::write(DateTime DateTime)
{
  Serial.print("M:"); Serial.println(DateTime.minute()/5);
  Serial.print("H:"); Serial.println(DateTime.hour()%12);
	  
  for(int addr = 0; addr<4; addr++)
  {
    for(int row = 0; row<8; row++)
    {
	  
     // LedControlConventional.setRow(addr, row, MINUTE_SPRITES[0][addr][row] | HOUR_SPRITES[9][addr][row]);
	  LedControlConventional.setRow(addr, row, MINUTE_SPRITES[DateTime.minute()/5][addr][row] | HOUR_SPRITES[DateTime.hour()%12][addr][row]);
	}
  }
}

void ConventionalDisplay::setIntensity(int intensity)
{
  for(int addr = 0; addr<4; addr++)
  {
    LedControlConventional.setIntensity(addr, intensity);
  }
}

////////////////////////////////////////////////
DigitalDisplay::DigitalDisplay(int dataPin, int clkPin, int csPin, int numDevices=1)
{
  LedControl temp(dataPin, clkPin, csPin, numDevices);
  
  LedControlDigital = temp;
}

void DigitalDisplay::write(DateTime DateTime)
{
  LedControlDigital.setDigit(0, 1, DateTime.hour()  /10, 0);
  LedControlDigital.setDigit(0, 1, DateTime.hour()  %10, 0);
  LedControlDigital.setDigit(0, 1, DateTime.minute()/10, 0);
  LedControlDigital.setDigit(0, 1, DateTime.minute()%10, 0);
}

void DigitalDisplay::setIntensity(int intensity)
{
  LedControlDigital.setIntensity(0, intensity);
}