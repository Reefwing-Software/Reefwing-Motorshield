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

#endif // _TARGET_H