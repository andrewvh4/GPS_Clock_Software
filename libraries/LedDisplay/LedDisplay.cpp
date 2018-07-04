#include "LedDisplay.h"

#include "DateTime.h"
#include "RTClib.h"
#include "LedControl_modified.h"
#include <Arduino.h>



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
  LedControlBinary.setRow(0, 7, (int8_t) DateTime.year() -2000   );
  LedControlBinary.setRow(0, 6, (int8_t) DateTime.month()        );
  LedControlBinary.setRow(0, 5, (int8_t) DateTime.day()          );
  LedControlBinary.setRow(0, 4, (int8_t) DateTime.weekOfTheYear());
  LedControlBinary.setRow(0, 3, (int8_t) DateTime.dayOfTheWeek() );
  LedControlBinary.setRow(0, 2, (int8_t) DateTime.hour()         );
  LedControlBinary.setRow(0, 1, (int8_t) DateTime.minute()       );
  LedControlBinary.setRow(0, 0, (int8_t) DateTime.second()       );
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
}

void ConventionalDisplay::write(DateTime DateTime)
{
  for(int addr = 0; addr<4; addr++)
  {
    for(int row = 0; row<7; row++)
    {
	  LedControlConventional.setRow(addr, row, MINUTE_SPRITES[DateTime.minute()/12][addr][row] | HOUR_SPRITES[DateTime.hour()/12][addr][row]);
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