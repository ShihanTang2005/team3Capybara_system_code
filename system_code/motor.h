#ifndef MOTOR_H
#define MOTOR_H

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

void motorSetup();
void goForward();
void goBackward();
void rotateClockwise();
void rotateCounterClockwise();
void stopMotors();

#endif
