/******************************************************************
  @file       ReefwingMotorShield.cpp
  @brief      Arduino Library for the Reefwing Motor Shield
  @author     David Such
  @copyright  Please see the accompanying LICENSE file.

  Code:        David Such
  Version:     3.0
  Date:        14/12/22

  1.0 Original Release          27/07/21
  1.1 Updated Examples          10/08/21
  2.0 Added Nano 33 IoT support 08/12/21
  3.0 Rebrand & New Repo        14/12/22

******************************************************************/

#include "Arduino.h"
#include "ReefwingMotorShield.h"

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
    //  #error DCMotor exception - channel has to be 1 or 2.
  }
}

void DCMotor::enable(void) {
  digitalWrite(_enablePin, HIGH);
}

void DCMotor::disable(void) {
  digitalWrite(_enablePin, LOW);
}

void DCMotor::setConfiguration(uint8_t config) {
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
    case DISCONNECT:
      disable();
      digitalWrite(_input1Pin, LOW);
      digitalWrite(_input2Pin, LOW);
      break;
    default:
      //  #error DCMotor exception - Invalid configuration option.
      break;
  }
}

void DCMotor::setSpeed(uint8_t speed) {
  if (speed >= 0 && speed < 256) {
    analogWrite(_enablePin, speed);
  }
  else {
    //  #error DCMotor exception - Speed not within valid range (0-255).
  }
}

uint8_t DCMotor::getChannel(void) {
  return _channel;
}

uint8_t DCMotor::getEnablePin(void) {
  return _enablePin;
}

uint8_t DCMotor::getInput1Pin(void) {
  return _input1Pin;
}

uint8_t DCMotor::getInput2Pin(void) {
  return _input2Pin;
}

DCMotor getMotor(uint8_t channel) {
  return DCMotor(channel);
}

ReefwingMotorShield::ReefwingMotorShield(void): motor1{ getMotor(1) }, motor2{ getMotor(2) } {
  //  Pin Configuration
  pinMode(VBAT, INPUT);
  if (BOARD_NAME  == NANO_33_IOT) pinMode(BUZZER, OUTPUT);

  //  Disable & Disconnect Motors on start
  motor1.setConfiguration(DISCONNECT);
  motor2.setConfiguration(DISCONNECT);
}

void ReefwingMotorShield::setR1(uint16_t r1) {
  _r1 = r1;
}

void ReefwingMotorShield::setR2(uint16_t r2) {
  _r2 = r2;
}

uint16_t ReefwingMotorShield::getR1(void) {
  return _r1;
}
        
uint16_t ReefwingMotorShield::getR2(void) {
  return _r2;
}

float ReefwingMotorShield::readDividerRatio(void) {
  return (float)(_r1 + _r2) / (float)_r2;
}

float ReefwingMotorShield::readADCValue(void) {
  //  ADC Hardware rounds down
  return (float)analogRead(VBAT) + 0.5;
}

float ReefwingMotorShield::readBatteryVoltage(void) {
  float adcValue = readADCValue(); 

  return (adcValue / 1024.0) * VLOGIC * readDividerRatio();
}