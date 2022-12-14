/******************************************************************
  @file       accelerate.ino
  @brief      Accelerate DCMotor example for the Reefwing Motor Shield
  @author     David Such
  @copyright  Please see the accompanying LICENSE file.

  Code:        David Such
  Version:     3.0
  Date:        14/12/22

  1.0 Original Release          27/07/21
  1.1 Updated Examples          10/08/21
  3.0 Rebrand & New Repo        14/12/22

******************************************************************/

#include <ReefwingMotorShield.h>

ReefwingMotorShield motorShield;

void setup() {
    // DEBUG
    Serial.begin(115200);

    //  For the Nano 33 IoT uncomment the next line
    //  while (!Serial);    
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
    delay(2000);

    // Decelerate in REVERSE direction
    decelerate();
    coast();
    delay(2000);
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