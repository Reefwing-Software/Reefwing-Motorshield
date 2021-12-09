/******************************************************************
  @file    NexgenMotorShield.h
  @brief   Arduino Library for the Nexgen Motor Shield
  @author  David Such

  Code:        David Such
  Version:     2.0
  Date:        08/12/21

  1.0 Original Release          27/07/21
  1.1 Updated Examples          10/08/21
  2.0 Added Nano 33 IoT support 08/12/21

******************************************************************/

#ifndef NexgenMotorShield_h
#define NexgenMotorShield_h

#include "Arduino.h"
#include "target.h"

/******************************************************************
 *  DCMotor Configuration Options
 * 
 ******************************************************************/

#define FORWARD     1
#define REVERSE     2
#define BRAKE       3
#define COAST       4
#define DISCONNECT  5

/******************************************************************
 *  DCMotor Class
 * 
 ******************************************************************/

class DCMotor {
    public:
        DCMotor(uint8_t);

        void enable(void);
        void disable(void);
        void setConfiguration(uint8_t);
        void setSpeed(uint8_t);
        uint8_t getChannel(void);
        uint8_t getEnablePin(void);
        uint8_t getInput1Pin(void);
        uint8_t getInput2Pin(void);

    private:
        uint8_t _enablePin, _input1Pin, _input2Pin;
        uint8_t _channel;
};

/******************************************************************
 *  NexgenMotorShield Class
 * 
 ******************************************************************/

class NexgenMotorShield {
    public:
        NexgenMotorShield(void);

        DCMotor motor1, motor2;

        void setR1(uint16_t);
        void setR2(uint16_t);
        uint16_t getR1(void);
        uint16_t getR2(void);
        float readADCValue(void);
        float readDividerRatio(void);
        float readBatteryVoltage(void);
        String NexgenMotorShield::boardName()

    private:
      uint16_t _r1 = R1; 
      uint16_t _r2 = R2;
};

#endif