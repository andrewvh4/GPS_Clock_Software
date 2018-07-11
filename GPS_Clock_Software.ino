#include "LedControl_modified.h"
#include "GPS_Clock_Software.h"
#include "DateTime.h"
#include "RTClib.h"
#include "Adafruit_GPS_modified.h"
#include <SoftwareSerial.h>

#include "LedDisplay.h"

bool usingInterrupt = false;

DateTime PreviousDateTime;
DateTime DateTime;
TimeSpan TimeOffset;

//GPS recieves on D2, sends on D3
SoftwareSerial GPSSerial(3, 2);
Adafruit_GPS GPS(&GPSSerial);

bool readGPS();
void setTime();
void displayTime();
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Initialised");

  GPS.begin(9600);

  delay(100);
  //Set Sentences to Use
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  //Set update Rate
 // GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);

  delay(100);

  useInterrupt(false);
  Display.setIntensity(1);
}

void loop() {
  bool gps_parsed = readGPS();

  if(gps_parsed)
  {
    //Serial.println("Display");
    setTime();
    if(!(PreviousDateTime == DateTime))
    {
      displayTime();
    }
    PreviousDateTime = DateTime;
  }
}

bool readGPS()
{ 
  bool parsed =  false;
  char c = GPS.read();
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) 
  {
    if (!GPS.parse(GPS.lastNMEA() ) )// this also sets the newNMEAreceived() flag to false
    {
      return false;  // we can fail to parse a sentence in which case we should just wait for another
    }//end if
  
  parsed = true;
  }//end if
  return parsed;
}

void setTime()
{
  DateTime.set(GPS.year, GPS.month, GPS.day, GPS.hour, GPS.minute, GPS.seconds);
  if(!USEUTC)
  {
    if(DateTime.isInDST() && USETAUTODST)
    {
      TimeOffset = TIMEZONE + DST;
    }
    else 
    {
      TimeOffset = TIMEZONE;
    }
    DateTime = DateTime + TimeOffset;
    
    if(_12HOURCLOCK)
    {
      DateTime.hh %= 12;
      if(DateTime.hh == 0) DateTime.hh = 12;
    }
  }
  
}

void displayTime()
{
 /* Serial.print("Quality:"); Serial.print(GPS.fixquality);
  Serial.print("\nTime: ");
  Serial.print(DateTime.hour(), DEC); Serial.print(':');
  Serial.print(DateTime.minute(), DEC); Serial.print(':');
  Serial.println(DateTime.second(), DEC);
  Serial.print("Date: ");
  Serial.print(DateTime.day(), DEC); Serial.print('/');   
  Serial.print(DateTime.month(), DEC); Serial.print("/");
  Serial.println(DateTime.year(), DEC); 
  Serial.println("");
  */
  Display.write(DateTime); 
}

//Interrupt Funcions
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  Serial.print(c);
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}
