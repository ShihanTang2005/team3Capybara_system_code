#include "Xbee.h"

///////Global variables//////////
/////temp_sensor////
extern float tempSensorValue;
/////mpu//////
extern  float Accel_final[3];
extern  float Gyro_final[3];

/////bmp280//////
extern float bme_pressure;
extern float bme_altitude;
/////GPS////////
extern float lat;
extern float lng;
extern float alt;
/////////////////////////
extern Canset_state State;
////////////////////////////////



void xbee_setup() {
}

void xbee_loop() {
  // Format data into a CSV string
  String dataPacket = String(millis()) + ";";
  dataPacket += String(lat) + ";";
  dataPacket += String(lng) + ";";
  dataPacket += String(alt) + ";";
  dataPacket += String(bme_pressure) + ";";
  dataPacket += String(bme_altitude) + ";";
  dataPacket += String(tempSensorValue) + ";";
  dataPacket += String(Accel_final[0]) + ";";
  dataPacket += String(Accel_final[1]) + ";";
  dataPacket += String(Accel_final[2]) + ";";
  dataPacket += String(Gyro_final[0]) + ";";
  dataPacket += String(Gyro_final[1]) + ";";
  dataPacket += String(Gyro_final[2]) + ";";
  dataPacket += String(State); // Assuming State can also be converted to String
  
  // Send the formatted data via XBee
  Serial.println(dataPacket);  
}
