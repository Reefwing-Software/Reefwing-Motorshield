// Copyright (c) 2022 dsuch
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

/******************************************************************
 * Definition loading based on detected hardware
 * 
 ******************************************************************/

#include <Arduino.h>

#ifndef _TARGET_H    
#define _TARGET_H

#define UNO         "Arduino UNO R3"
#define NANO_33_IOT "Arduino Nano 33 IoT"

#if defined(ARDUINO_AVR_UNO)
  #include "uno.h"
#elif defined(ARDUINO_ARCH_SAMD)
  #include "nano33iot.h"
#else
  #error "Unsupported Hardware"
#endif  // target detection

#endif // _TARGET_H