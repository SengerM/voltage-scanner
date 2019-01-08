#include "Delay.h"

void delay_milliseconds(unsigned long mil) {
	// I was forced to write this function because the built in functions
	// "delay" and "millis" kill the serial communication. I have no idea
	// why, but they do...
	unsigned long i = 0;
	unsigned long cycles = mil*1e3/(CLK_FREQ);
	while (++i < cycles) ;
	return;
}
