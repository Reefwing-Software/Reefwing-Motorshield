/******************************************************************
  @file    NexgenMotorShield.h
  @brief   Arduino Library for the Nexgen Motor Shield
  @author  David Such

  Code:        David Such
  Version:     1.0
  Date:        27/07/21

  1.0 Original Release          27/07/21

******************************************************************/

#ifndef NexgenMotorShield_h
#define NexgenMotorShield_h

#include "Arduino.h"

#define M1_ENABLE 3
#define M1_INPUT1 2
#define M1_INPUT2 4

#define M2_ENABLE 11
#define M2_INPUT1 7
#define M2_INPUT2 8

#define SERVO1    9
#define SERVO2    10

/******************************************************************
   DCMotor Configuration Options
 ******************************************************************/

#define FORWARD   1
#define REVERSE   2
#define BRAKE     3
#define COAST     4

/******************************************************************
   Battery Voltage ADC DEFINES
 ******************************************************************/

#define R1        10000 // 10K
#define R2        6800  // 6K8
#define VBAT      14    // Analogue Pin A0

class DCMotor {
    public:
        DCMotor(uint8_t channel);

        void enable();
        void disable();
        void setConfiguration(uint8_t config);
        void setSpeed(uint8_t speed);

    private:
        uint8_t _enablePin, _input1Pin, _input2Pin;
        uint8_t _channel;
};

class NexgenMotorShield {
    public:
        NexgenMotorShield();

        DCMotor motor1, motor2;

        void setR1(uint8_t r1);
        void setR2(uint8_t r2);
        float readADCValue();
        float readDividerRatio();
        float readBatteryVoltage();

    private:
      uint8_t _r1, _r2;
};

#endif