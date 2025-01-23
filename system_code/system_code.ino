#include <Wire.h>
#include <Adafruit_BMP280.h>
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
}

void sensor_loop(){
  temp_sensor_loop();
  mpu_loop();
  bmp280_loop();
}


void temp_sensor_setup(){}

void temp_sensor_loop(){

  tempSensorValue = analogRead(analogInPin);
  tempSensorValue = tempSensorValue*5000/1023*1/10;
  Serial.println(tempSensorValue,1);
}


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


void bmp280_setup(){
  bme.begin();
}

void bmp280_loop(){
  Serial.print("BMP pressure: ");Serial.print(bme.readPressure()/100);Serial.println("[hPa]");
    Serial.print("Altitude: ");Serial.print(bme.readAltitude(1013.25));Serial.println("[m]");
}
