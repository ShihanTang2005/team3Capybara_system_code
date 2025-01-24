#include <Servo.h>
#include "servo.h"
#include "Arduino.h"
Servo myServo;

void servo_setup() {
  myServo.attach(9);   
  myServo.write(0);
}

void servo_loop() {
}

void open_servo() {
  myServo.write(90);   
  delay(1000);         
  myServo.detach();   
}
