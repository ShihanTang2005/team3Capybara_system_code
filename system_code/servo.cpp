#include <Servo.h>
#include "servo.h"

Servo myServo;

void servo_setup() {
  myServo.attach(9);   
  myServo.write(0);
}

void servo_loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "open") {
      open_servo();
    }
  }
}

void open_servo() {
  myServo.write(90);   
  delay(1000);         
  myServo.detach();   
}
