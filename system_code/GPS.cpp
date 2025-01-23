#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "GPS.h"
// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

float lat = 0;
float lng = 0;
float alt = 0;


void GPS_setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
}

void GPS_loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      GPS_displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
  }
}

void GPS_displayInfo()
{
  if (gps.location.isValid()){
    GPS_displayInfo_ON();
  }
  else{
    GPS_displayInfo_OFF();
  }
}


void GPS_displayInfo_ON(){
    lat = gps.location.lat();
    lng = gps.location.lng();
    alt = gps.altitude.meters();
  
//  Serial.print("Date: ");
//    Serial.print(gps.date.month());
//    Serial.print("/");
//    Serial.print(gps.date.day());
//    Serial.print("/");
//    Serial.println(gps.date.year());

//  Serial.print("Time: ");
//    if (gps.time.hour() < 10) Serial.print(F("0"));
//    Serial.print(gps.time.hour());
//    Serial.print(":");
//    if (gps.time.minute() < 10) Serial.print(F("0"));
//    Serial.print(gps.time.minute());
//    Serial.print(":");
//    if (gps.time.second() < 10) Serial.print(F("0"));
//    Serial.print(gps.time.second());
//    Serial.print(".");
//    if (gps.time.centisecond() < 10) Serial.print(F("0"));
//    Serial.println(gps.time.centisecond());
//  Serial.println();
//  Serial.println();
}

void GPS_displayInfo_OFF(){
  lat = -1;
  lng = -1;
  alt = -1;
}
