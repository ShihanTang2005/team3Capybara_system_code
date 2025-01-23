#include "Xbee.h"

void xbee_setup() {
  Serial1.begin(9600); 
  Serial1.println("XBee initialized"); 
}

void xbee_loop() {
  // Collect sensor data
  String gpsData = GPS_get_data();       
  float pressure = bmp280_readPressure(); 
  float temperature = temp_sensor_read(); 
  float accelX = mpu_getAccelX();      

  // Format data into a CSV string
  String dataPacket = String("Time: ") + millis() + ", ";
  dataPacket += "GPS: " + gpsData + ", ";
  dataPacket += "Pressure: " + String(pressure, 2) + ", ";
  dataPacket += "AccelX: " + String(accelX, 2) + ", ";
  dataPacket += "Temp: " + String(temperature, 2);

  // Send the formatted data via XBee
  Serial1.println(dataPacket); 
  Serial.println(dataPacket);  
}
