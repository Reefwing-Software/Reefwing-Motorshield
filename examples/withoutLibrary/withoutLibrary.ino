/******************************************************************
  @file    withoutLibrary.ino
  @brief   Using the UNO Nexgen Motor Shield without the Library
  @author  David Such

  Code:        David Such
  Version:     2.0
  Date:        10/08/21

  1.0 Original Release          27/07/21
  1.1 Updated Examples          10/08/21
  2.0 Added Nano comments       08/12/21

  Note:   The pin and other definitions are for the UNO shield,
          you will need to manually change these if you are using
          the Nano 33 IoT Carrier Board. Look in nano33iot.h for the
          correct definitions for this board.

******************************************************************/

#define M1_ENABLE 3
#define M1_INPUT1 2
#define M1_INPUT2 4

#define M2_ENABLE 11
#define M2_INPUT1 7
#define M2_INPUT2 8

#define SERVO1    9
#define SERVO2    10

/******************************************************************
   Battery Voltage ADC
 ******************************************************************/

#define R1        10000 // 10K
#define R2        6800  // 6K8
#define VBAT      14    // Analogue Pin A0
#define VLOGIC    5.0   //  UNO has 5V logic

#define BOARD_NAME  UNO

float batteryVoltage = 0.0;
const float dividerRatio = (float)(R1 + R2) / (float)R2;

/******************************************************************
   SETUP
 ******************************************************************/

void setup() {
  //  Pin Configuration
  pinMode(M1_ENABLE, OUTPUT);
  pinMode(M1_INPUT1, OUTPUT);
  pinMode(M1_INPUT2, OUTPUT);
  pinMode(M2_ENABLE, OUTPUT);
  pinMode(M2_INPUT1, OUTPUT);
  pinMode(M2_INPUT2, OUTPUT);

  pinMode(VBAT, INPUT);

  //  Disable Motors on start
  freeRunStop();

  //  Serial for Debugging
  Serial.begin(115200);
}

/******************************************************************
   LOOP
 ******************************************************************/

void loop() {
  float adcValue = (float)analogRead(VBAT) + 0.5; //  ADC Hardware rounds down

  batteryVoltage = (adcValue / 1024.0) * VLOGIC * dividerRatio;
  directionTest();
  speedTest();

  //  DEBUG
  Serial.print("Divider Ratio: ");
  Serial.print(dividerRatio);
  Serial.print(", ADC Value: ");
  Serial.print(adcValue);
  Serial.print(", Battery Voltage: ");
  Serial.println(batteryVoltage);
}

/******************************************************************
   MOTOR FUNCTIONS
 ******************************************************************/

void enableMotors() {
  digitalWrite(M1_ENABLE, HIGH);
  digitalWrite(M2_ENABLE, HIGH);
}

void activeBrake() {
  //  Best to avoid - can generate significant back EMF
  enableMotors();
  digitalWrite(M1_INPUT1, LOW);
  digitalWrite(M1_INPUT2, LOW);
  digitalWrite(M2_INPUT1, LOW);
  digitalWrite(M2_INPUT2, LOW);
}

void freeRunStop() {
  digitalWrite(M1_ENABLE, LOW);
  digitalWrite(M2_ENABLE, LOW);
}

void fastForward() {
  forward();
  enableMotors();
}

void fastReverse() {
  reverse();
  enableMotors();
}

void forward() {
  digitalWrite(M1_INPUT1, HIGH);
  digitalWrite(M1_INPUT2, LOW);
  digitalWrite(M2_INPUT1, HIGH);
  digitalWrite(M2_INPUT2, LOW);
}

void reverse() {
  digitalWrite(M1_INPUT1, LOW);
  digitalWrite(M1_INPUT2, HIGH);
  digitalWrite(M2_INPUT1, LOW);
  digitalWrite(M2_INPUT2, HIGH);
}

void accelerate() {
  for (int i = 0; i < 256; i++) {
    analogWrite(M1_ENABLE, i);
    analogWrite(M2_ENABLE, i);
    delay(20);
  }
}

void decelerate() {
  for (int i = 255; i >= 0; --i) {
    analogWrite(M1_ENABLE, i);
    analogWrite(M2_ENABLE, i);
    delay(20);
  }
}

void directionTest() {
  fastForward();      //  M1 & M2 Forward Direction (CCW), Speed 100%
  delay(1000);
  freeRunStop();
  delay(1000);
  fastReverse();      //  M1 & M2 Reverse Direction (CW), Speed 100%
  delay(1000);
  freeRunStop();
  delay(1000);
}

void speedTest() {
  //  Set Motor Direction
  forward();
  accelerate();
  decelerate();
  freeRunStop();
  delay(1000);
}
