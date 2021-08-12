/******************************************************************
  @file    batteryVoltage.ino
  @brief   Battery monitoring example for the Nexgen Motor Shield
  @author  David Such

  Code:        David Such
  Version:     1.1
  Date:        10/08/21

  1.0 Original Release          27/07/21
  1.1 Updated Examples          10/08/21

******************************************************************/

#include <NexgenMotorShield.h>

NexgenMotorShield motorShield;

void setup() {
    //  Set voltage divider resistor values if not the defaults (in ohms)
    //  motorShield.setR1(10000);
    //  motorShield.setR2(6800);

    //  Serial for Debugging
    Serial.begin(115200);
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