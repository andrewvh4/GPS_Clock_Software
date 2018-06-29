#include "LedControl_modified.h"
#include "GPS_Clock_Software.h"
#include "DateTime.h"
#include "RTClib.h"

#include "LedDisplay.h"

const int dataPin = 1;
const int clkPin  = 2;
const int csPin   = 3;


DateTime DateTime;
ConventionalDisplay Display(dataPin, clkPin, clkPin);



void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

}

