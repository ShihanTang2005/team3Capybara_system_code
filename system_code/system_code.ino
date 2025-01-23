#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "mpu.h"
#include "GPS.h"
///////constant variable///////
/////////temp_sensor/////////
const int analogInPin = A3;
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
float tempSensorValue = 0;
/////mpu//////
extern byte Temp_H ;
extern  byte Temp_L ;
extern  float Accel[3];
extern  float Gyro[3];

/////bmp280//////
Adafruit_BMP280 bme;
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

void setup() {
  Serial.begin(9600);
  //Our code starts here.
  sensor_setup();

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
}

void sensor_loop(){
  temp_sensor_loop();
  mpu_loop();
  bmp280_loop();
  GPS_loop();
}


void temp_sensor_setup(){}

void temp_sensor_loop(){

  tempSensorValue = analogRead(analogInPin);
  tempSensorValue = tempSensorValue*5000/1023*1/10;
  Serial.println(tempSensorValue,1);
}




void bmp280_setup(){
  bme.begin();
}

void bmp280_loop(){
  Serial.print("BMP pressure: ");Serial.print(bme.readPressure()/100);Serial.println("[hPa]");
    Serial.print("Altitude: ");Serial.print(bme.readAltitude(1013.25));Serial.println("[m]");
}
