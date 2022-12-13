/******************************************************************
  @file    batteryVoltage.ino
  @brief   Battery monitoring example for the Reefwing Motor Shield
  @author  David Such

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
    //  Set voltage divider resistor values if not the defaults (in ohms)
    //  motorShield.setR1(10000);
    //  motorShield.setR2(6800);

    //  Serial for Debugging
    Serial.begin(115200);
    while (!Serial);
}

void loop() {
    //  DEBUG
    Serial.print("R1 : ");
    Serial.print(motorShield.getR1());
    Serial.print(", R2 : ");
    Serial.print(motorShield.getR2());
    Serial.print(", Divider Ratio: ");
    Serial.print(motorShield.readDividerRatio());
    Serial.print(", ADC Value: ");
    Serial.print(motorShield.readADCValue());
    Serial.print(", Battery Voltage: ");
    Serial.println(motorShield.readBatteryVoltage());
    delay(1000);
}