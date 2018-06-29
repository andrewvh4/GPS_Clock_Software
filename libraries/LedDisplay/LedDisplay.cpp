#include "LedDisplay.h"

#include "DateTime.h"
#include "RTClib.h"
#include "LedControl_modified.h"



//////////////////////////////////////////////////////////////////////////////////
BinaryDisplay::BinaryDisplay(int dataPin, int clkPin, int csPin, int numDevices=1)
{
  LedControl temp(dataPin, clkPin, csPin, numDevices);
  LedControlClass = temp;
}

void BinaryDisplay::write(DateTime DateTime)
{
  LedControlClass.setColumn(0, 0, (int8_t) DateTime.year()         );
  LedControlClass.setColumn(0, 1, (int8_t) DateTime.month()        );
  LedControlClass.setColumn(0, 2, (int8_t) DateTime.day()          );
  LedControlClass.setColumn(0, 3, (int8_t) DateTime.weekOfTheYear());
  LedControlClass.setColumn(0, 4, (int8_t) DateTime.dayOfTheWeek() );
  LedControlClass.setColumn(0, 5, (int8_t) DateTime.hour()         );
  LedControlClass.setColumn(0, 6, (int8_t) DateTime.minute()       );
  LedControlClass.setColumn(0, 7, (int8_t) DateTime.second()       );
}

void BinaryDisplay::setIntensity(int intensity)
{
  LedControlClass.setIntensity(0, intensity);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
ConventionalDisplay::ConventionalDisplay(int dataPin, int clkPin, int csPin, int numDevices=4)
{
  LedControl temp(dataPin, clkPin, csPin, numDevices);
  LedControlClass = temp;
}

void ConventionalDisplay::write(DateTime DateTime)
{
  for(int addr = 0; addr<4; addr++)
  {
    for(int row = 0; row<7; row++)
    {
	  LedControlClass.setRow(addr, row, MINUTE_SPRITES[DateTime.minute()/12][addr][row] | HOUR_SPRITES[DateTime.hour()/12][addr][row]);
	}
  }
}

void ConventionalDisplay::setIntensity(int intensity)
{
  for(int addr = 0; addr<4; addr++)
  {
    LedControlClass.setIntensity(addr, intensity);
  }
}

////////////////////////////////////////////////
DigitalDisplay::DigitalDisplay(int dataPin, int clkPin, int csPin, int numDevices=1)
{
  LedControl temp(dataPin, clkPin, csPin, numDevices);
  LedControlClass = temp;
}

void DigitalDisplay::write(DateTime DateTime)
{
  LedControlClass.setDigit(0, 1, DateTime.hour()  /10, 0);
  LedControlClass.setDigit(0, 1, DateTime.hour()  %10, 0);
  LedControlClass.setDigit(0, 1, DateTime.minute()/10, 0);
  LedControlClass.setDigit(0, 1, DateTime.minute()%10, 0);
}

void DigitalDisplay::setIntensity(int intensity)
{
  LedControlClass.setIntensity(0, intensity);
}