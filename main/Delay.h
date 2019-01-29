#ifndef _DELAY_H_
#define _DELAY_H_

#include <Arduino.h>

#define _UGLY_DELAY_CALIB_ (9999999.0/3.75/1000.0) // This calibration value was determined on 29 January 2019 usign an Arduino Uno in standard clock configuration.

void delay_milliseconds(unsigned long mil);

#endif
