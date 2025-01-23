#include "mpu.h"
#include <Arduino.h>
#include <Wire.h>
const int MPU_addr = 0x68;
const byte PWR_MGMT_1 = 0x6B;
const byte WHO_AM_I = 0X75;
const byte Temp_1 = 0x41;
const byte Accel_1 = 0x3B;
const byte Accel_conf = 0x1C;
const byte Gyro_conf = 0x1B;

byte Temp_H = 0;
  byte Temp_L = 0;
  float Accel[3]={0};
  float Gyro[3]={0};
void mpu_setup(){
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Wire.beginTransmission(0x68);
    Wire.write(Accel_conf);
    Wire.write(0x10);
    Wire.endTransmission(true);
    Wire.beginTransmission(0x68);
    Wire.write(Gyro_conf);
    Wire.write(0x08);
    Wire.endTransmission(true);
}

void mpu_loop(){

    Wire.beginTransmission(MPU_addr);
    Wire.write(Accel_1);
    Wire.endTransmission();
    Wire.requestFrom(MPU_addr,14);
    for(int i=0;i<3;i++){
        Accel[i]=Wire.read()<<8|Wire.read();
    }
    Temp_H = Wire.read();
    Temp_L = Wire.read();
    for(int i=0;i<3;i++){
        Gyro[i]=Wire.read()<<8|Wire.read();
    }
//  Serial.print("Acceleration is ----");
    float Accel_final[3]={0};
    for(int i=0;i<3;i++){
        Accel_final[i] = (float)Accel[i]/4096;
    }
    float Gyro_final[3]={0};
    for(int i=0;i<3;i++){
        Gyro_final[i] = (float)Accel[i]/65.5;
    }
    Serial.print("Acc-x[g]:");
    Serial.print(Accel_final[0]);
    Serial.print(" ");
    Serial.print("Acc-y[g]:");
    Serial.print(Accel_final[1]);
    Serial.print(" ");
    Serial.print("Acc-z[g]:");
    Serial.print(Accel_final[2]);
    Serial.print("Gyro-x[g]:");
    Serial.print(Gyro_final[0]);
    Serial.print(" ");
    Serial.print("Gyro-y[g]:");
    Serial.print(Gyro_final[1]);
    Serial.print(" ");
    Serial.print("Gyro-z[g]:");
    Serial.println(Gyro_final[2]);
//  Serial.println("");
//  Serial.print("temp is ----");
//  int temp_out = Temp_H<<8|Temp_L;
//  temp_out = temp_out/340 + 36.53;
//  Serial.println(temp_out);
}
