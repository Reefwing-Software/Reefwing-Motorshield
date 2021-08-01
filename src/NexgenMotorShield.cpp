/******************************************************************
  @file    NexgenMotorShield.cpp
  @brief   Arduino Library for the Nexgen Motor Shield
  @author  David Such

  Code:        David Such
  Version:     1.0
  Date:        27/07/21

  1.0 Original Release          27/07/21

******************************************************************/

#include "Arduino.h"
#include "NexgenMotorShield.h"

DCMotor::DCMotor(uint8_t channel) {
  _channel = channel;

  if (channel == 1) {
    pinMode(M1_ENABLE, OUTPUT);
    pinMode(M1_INPUT1, OUTPUT);
    pinMode(M1_INPUT2, OUTPUT);

    _enablePin = M1_ENABLE, 
    _input1Pin = M1_INPUT1, 
    _input2Pin = M1_INPUT2;
  }
  else if (channel == 2) {
    pinMode(M2_ENABLE, OUTPUT);
    pinMode(M2_INPUT1, OUTPUT);
    pinMode(M2_INPUT2, OUTPUT);

    _enablePin = M2_ENABLE, 
    _input1Pin = M2_INPUT1, 
    _input2Pin = M2_INPUT2;
  }
  else {
    #error DCMotor exception - channel has to be 1 or 2.
  }
}

DCMotor::enable() {
  digitalWrite(_enablePin, HIGH);
}

DCMotor::disable() {
  digitalWrite(_enablePin, LOW);
}

DCMotor::setConfiguration(uint8_t config) {
  switch(config) {
    case FORWARD:
      digitalWrite(_input1Pin, HIGH);
      digitalWrite(_input2Pin, LOW);
      break;
    case REVERSE:
      digitalWrite(_input1Pin, LOW);
      digitalWrite(_input2Pin, HIGH);
      break;
    case BRAKE:
      //  Best to avoid - can generate significant back EMF
      //  Use COAST instead.
      enable();
      digitalWrite(_input1Pin, LOW);
      digitalWrite(_input2Pin, LOW);
      break;
    case COAST:
      disable();
      break;
    default:
      #error DCMotor exception - Invalid configuration option.
      break;
  }
}

DCMotor::setSpeed(uint8_t speed) {
  if (speed >= 0 && speed < 256) {
    analogWrite(_enable, speed);
  }
  else {
    #error DCMotor exception - Speed not within valid range (0-255).
  }
}

NexgenMotorShield::NexgenMotorShield {
  //  Voltage divider resistor defaults
  _r1 = R1;
  _r2 = R2;

  //  Pin Configuration
  pinMode(VBAT, INPUT);

  //  Initialise Motors
  motor1 = DCMotor(1);
  motor2 = DCMotor(2);

  //  Disable Motors on start
  motor1.disable();
  motor2.disable();
}

NexgenMotorShield::setR1(uint8_t r1) {
  _r1 = r1;
}

NexgenMotorShield::setR2(uint8_t r2) {
  _r2 = r2;
}

NexgenMotorShield::readDividerRatio() {
  return (float)(_r1 + _r2) / (float)_r2;
}

NexgenMotorShield::readADCValue() {
  //  ADC Hardware rounds down
  return (float)analogRead(VBAT) + 0.5;
}

NexgenMotorShield::readBatteryVoltage() {
  float adcValue = readADCValue(); 

  return (adcValue / 1024.0) * 5.0 * readDividerRatio();
}