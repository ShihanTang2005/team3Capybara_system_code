#include "temp_sensor.h"
const int analogInPin = A3;
float tempSensorValue = 0;
void temp_sensor_setup(){}

void temp_sensor_loop(){

  tempSensorValue = analogRead(analogInPin);
  tempSensorValue = tempSensorValue*5000/1023*1/10;
}