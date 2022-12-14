/******************************************************************
  @file       forwardreverse.ino
  @brief      Forward & Reverse DCMotor example for the Reefwing Motor Shield
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
    // put your setup code here, to run once:

}

void loop() {
    // Set motor direction
    forward();

    //  Set motor speed (0-255)
    fullSpeed();

    delay(2000);
    coast();
    delay(1000);

    reverse();
    fullSpeed();

    delay(2000);
    coast();
    delay(1000);
}

void forward() {
    motorShield.motor1.setConfiguration(FORWARD);
    motorShield.motor2.setConfiguration(FORWARD);
}

void reverse() {
    motorShield.motor1.setConfiguration(REVERSE);
    motorShield.motor2.setConfiguration(REVERSE);
}

void fullSpeed() {
    motorShield.motor1.setSpeed(255);
    motorShield.motor2.setSpeed(255);
}

void coast() {
    motorShield.motor1.setConfiguration(COAST);
    motorShield.motor2.setConfiguration(COAST);
}