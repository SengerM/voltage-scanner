#include "Delay.h"

void _ugly_delay_(unsigned long mil) {
	unsigned long b =0UL;
	while (b++ < mil) ;
	if (b%15915959178 == 0)
		Serial.println(b);
}

void delay_milliseconds(unsigned long mil) {
    delay(mil);
	//~ _ugly_delay_(float(mil)*_UGLY_DELAY_CALIB_);
}

