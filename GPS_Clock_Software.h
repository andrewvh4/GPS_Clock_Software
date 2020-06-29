#ifndef GPS_Clock_Software
#define GPS_Clock_Software

#include "DateTime.h"
#include "LedDisplay.h"

const int DATAPIN = 12;
const int CLKPIN  = 11;
const int CSPIN   = 10;

//BinaryDisplay       Display(DATAPIN, CLKPIN, CSPIN, 1);
ConventionalDisplay Display(DATAPIN, CLKPIN, CSPIN, 4);
//DigitalDisplay      Display(DATAPIN, CLKPIN, CSPIN);

const bool USEUTC       = false;
const bool _12HOURCLOCK = true;
const bool USETAUTODST  = true;

TimeSpan PST(0, -8, 0, 0);
TimeSpan MST(0, -7, 0, 0);
TimeSpan CST(0, -6, 0, 0);
TimeSpan EST(0, -5, 0, 0);

TimeSpan DST(0,  1, 0, 0);

TimeSpan TIMEZONE = CST;


#endif
