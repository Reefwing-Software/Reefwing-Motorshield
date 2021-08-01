/******************************************************************
  @file    accelerate.ino
  @brief   Accelerate DCMotor example for the Nexgen Motor Shield
  @author  David Such

  Code:        David Such
  Version:     1.0
  Date:        01/08/21

  1.0 Original Release          01/08/21

******************************************************************/

#include <NexgenMotorShield>

NexgenMotorShield() motorShield;

void setup() {
    // put your setup code here, to run once:

}

void loop() {
    // put your main code here, to run repeatedly:
    accelerate();
    coast();
    delay(500);
    decelerate();
    coast();
    delay(500);
}

void accelerate() {
    motorShield.motor1.setConfiguration(FORWARD);
    motorShield.motor2.setConfiguration(FORWARD);
    for (int i = 0; i < 256; i++) {
        motorShield.motor1.setSpeed(i);
        motorShield.motor2.setSpeed(i);
        delay(20);
    }
}

void decelerate() {
    motorShield.motor1.setConfiguration(REVERSE);
    motorShield.motor2.setConfiguration(REVERSE);
    for (int i = 255; i >= 0; --i) {
        motorShield.motor1.setSpeed(i);
        motorShield.motor2.setSpeed(i);
        delay(20);
    }
}

void coast() {
    motorShield.motor1.setConfiguration(FORWARD);
    motorShield.motor2.setConfiguration(FORWARD);
}