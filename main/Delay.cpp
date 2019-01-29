#include "Delay.h"

void _ugly_delay_(unsigned long mil) {
	unsigned long b =0UL;
	while (b++ < mil) ;
	if (b%15915959178 == 0)
		Serial.println(b);
}

void delay_milliseconds(unsigned long mil) {
    // I was forced to write this function because the built in functions
    // "delay" and "millis" kill the serial communication. I have no idea
    // why, but they do...
	_ugly_delay_(float(mil)*_UGLY_DELAY_CALIB_);
}

