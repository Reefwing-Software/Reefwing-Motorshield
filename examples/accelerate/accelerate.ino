/******************************************************************
  @file    accelerate.ino
  @brief   Accelerate DCMotor example for the Nexgen Motor Shield
  @author  David Such

  Code:        David Such
  Version:     1.0
  Date:        01/08/21

  1.0 Original Release          01/08/21

******************************************************************/

#include <NexgenMotorShield.h>

NexgenMotorShield motorShield;

void setup() {
    // DEBUG
    Serial.begin(115200);
    Serial.print("Motor 1 : Channel - ");
    Serial.print(motorShield.motor1.getChannel());
    Serial.print(", Enable Pin - ");
    Serial.print(motorShield.motor1.getEnablePin());
    Serial.print(", Input 1 Pin - ");
    Serial.print(motorShield.motor1.getInput1Pin());
    Serial.print(", Input 2 Pin - ");
    Serial.println(motorShield.motor1.getInput2Pin());
}

void loop() {
    // Accelerate in FORWARD direction
    accelerate();
    coast();
    delay(1000);

    // Decelerate in REVERSE direction
    decelerate();
    coast();
    delay(1000);
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
    motorShield.motor1.setConfiguration(COAST);
    motorShield.motor2.setConfiguration(COAST);
}