#ifndef _ARDUINO_PINS_H_
#define _ARDUINO_PINS_H_

#define M2C_MODULE_PINS "\010\011\012" // See ASCII table https://en.cppreference.com/w/cpp/language/ascii and escape sequences in C https://en.wikipedia.org/wiki/Escape_sequences_in_C

#define LINE_A_STATUS_PIN 11
#define LINE_B_STATUS_PIN 2
#define CONNECT_STATUS_DETECTOR_PIN 3
#define DISCONNECT_STATUS_DETECTOR_PIN 4

#define CONNECT_DMM_TO_H_PIN 5
#define CONNECT_DMM_TO_L_PIN 6
#define DISCONNECT_DMM_PIN 7

#define ERROR_LOGGER_LED_PIN 13 // This pin indicates wheter there is an error or not.

#endif
