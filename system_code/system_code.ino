#include <Wire.h>
#include <Adafruit_BMP280.h>

#include "mpu.h"

///////constant variable///////
/////////temp_sensor/////////
const int analogInPin = A3;
/////////mpu////////////
const int MPU_addr = 0x68;
const byte PWR_MGMT_1 = 0x6B;
const byte WHO_AM_I = 0X75;
const byte Temp_1 = 0x41;
const byte Accel_1 = 0x3B;
const byte Accel_conf = 0x1C;
const byte Gyro_conf = 0x1B;
//////////////////////////////

///////states/////////
enum Canset_state={
  INFLIGHT,
  LANDED,
  ROVERING
};


///////Global variables//////////
/////temp_sensor////
float tempSensorValue = 0;
/////mpu//////
byte Temp_H = 0;
  byte Temp_L = 0;
  float Accel[3]={0};
  float Gyro[3]={0};

/////bmp280//////
Adafruit_BMP280 bme;
////////////////////////////////
  
void setup() {
  Serial.begin(9600);
  //Our code starts here.
    temp_sensor_setup();
    mpu_setup();
    bmp280_setup();
}



void loop() {
  //Our code starts here.
  temp_sensor_loop();
  mpu_loop();
  bmp280_loop();
  ///////////////
  delay(500);
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
