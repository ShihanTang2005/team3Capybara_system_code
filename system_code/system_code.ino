#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "mpu.h"
#include "GPS.h"
#include "bmp280.h"
#include "temp_sensor.h"
#include "Xbee.h"
#include "system_code.h"
#include "motor.h"
#include "servo.h"
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



Canset_state State=INFLIGHT;
int time_tick = 0;
int last_time_tick = 0;
int delay_time = 500; //ms

///// XBee initialization function////
//////////////////////////////////////

void setup() {
  Serial.begin(9600);
  //Our code starts here.
  sensor_setup();
  xbee_setup();
  servo_setup();
  motor_setup();
}

void loop() {
  //Our code starts here.
  sensor_loop();
  ///////////////
  launch_mission_under_State();
  ///////////////
  servo_loop();
  handleMotorCommands();
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


void handleMotorCommands() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove unnecessary whitespace

      // Execute motor commands
      if (command == "go") {
          goForward();
      } else if (command == "back") {
          goBackward();
      } else if (command == "clk1") {
          rotateClockwise();
      } else if (command == "clk2") {
          rotateCounterClockwise();
      } else if (command == "stop") {
          stopMotors();
      }
      if (command == "open") {
          open_servo();
      }
  }

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
  xbee_loop();
}
