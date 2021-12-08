/******************************************************************
 * Definition loading based on detected hardware
 * 
 ******************************************************************/

#include <Arduino.h>

#ifndef _TARGET_H    
#define _TARGET_H

#if defined(ARDUINO_AVR_UNO)
  #include "uno.h"
#elif defined(ARDUINO_ARCH_SAMD)
  #include "nano33iot.h"
#else
  #error "Unsupported Hardware"
#endif  // target detection
  
String boardType() {
  #if defined(ARDUINO_AVR_UNO)
    return "Arduino UNO R3";
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
    return "Arduino Nano 33 IoT";
  #else
    return "Board Unsupported.";
  #endif  // target detection
}

#endif // _TARGET_H