/******************************************************************
  @file    batteryVoltage.ino
  @brief   Battery monitoring example for the Nexgen Motor Shield
  @author  David Such

  Code:        David Such
  Version:     1.0
  Date:        01/08/21

  1.0 Original Release          01/08/21

******************************************************************/

#include <NexgenMotorShield>

NexgenMotorShield() motorShield;

void setup() {
    //  Set voltage divider resistor values if not default (in ohms)
    //  motorShield.setR1(10000);
    //  motorShield.setR2(6800);

    //  Serial for Debugging
    Serial.begin(115200);
}

void loop() {
    //  DEBUG
  Serial.print("Divider Ratio: ");
  Serial.print(motorShield.readDividerRatio());
  Serial.print(", ADC Value: ");
  Serial.print(motorShield.readADCValue());
  Serial.print(", Battery Voltage: ");
  Serial.println(motorShield.readBatteryVoltage());
    
}