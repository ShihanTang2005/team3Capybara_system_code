#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "mpu.h"
#include "GPS.h"
#include "bmp280.h"
#include "temp_sensor.h"
///////constant variable///////
/////////temp_sensor/////////

/////////mpu////////////
extern const int MPU_addr;
extern const byte PWR_MGMT_1;
extern const byte WHO_AM_I;
extern const byte Temp_1;
extern const byte Accel_1;
extern const byte Accel_conf;
extern const byte Gyro_conf;
//////////////////////////////

///////Global variables//////////
/////temp_sensor////

/////mpu//////
extern byte Temp_H ;
extern  byte Temp_L ;
extern  float Accel[3];
extern  float Gyro[3];

/////bmp280//////
////////////////////////////////
  

enum Canset_state{
  INFLIGHT,
  LANDED,
  ROVERING1,
  ROVERING2,
  RECOVERY
};
Canset_state State=INFLIGHT;
int time_tick = 0;
int last_time_tick = 0;
int delay_time = 500; //ms

///// XBee initialization function////
//////////////////////////////////////
void xbee_setup() {
  Serial1.begin(9600); 
  Serial1.println("XBee initialized"); 
}

void xbee_send_data() {
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


void setup() {
  Serial.begin(9600);
  //Our code starts here.
  sensor_setup();
  xbee_setup(); 
}

void loop() {
  //Our code starts here.
  sensor_loop();
  ///////////////
  launch_mission_under_State();
  ///////////////
  delay(delay_time);
  refresh_time_tick();
}


void switch_canset_state(){
  switch (State)
  {
  case INFLIGHT:
    State=LANDED;
    break;
  case LANDED:
    State=ROVERING1;
    break;
  case ROVERING1:
    State=ROVERING2;
    break;
  case ROVERING2:
    State=RECOVERY;
    break;
  case RECOVERY:
    break;
  default:
    break;
  }
}

void launch_mission_under_State(){
  if(State==INFLIGHT){}
  else if(State==LANDED){}
}

void refresh_time_tick(){

}

void sensor_setup(){
  temp_sensor_setup();
  mpu_setup();
  bmp280_setup();
  GPS_setup();
  xbee_setup(); 
}

void sensor_loop(){
  temp_sensor_loop();
  mpu_loop();
  bmp280_loop();
  GPS_loop();
  xbee_send_data();
}







