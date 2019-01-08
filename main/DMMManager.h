#ifndef _DMM_MANAGER_H_
#define _DMM_MANAGER_H_

#include <Arduino.h>
#include "RelayParameters.h"
#include "ErrorLogger.h"
#include "Delay.h"

enum DMMStatus {connected_to_H, connected_to_L, disconnected};

class DMMManager {
private:
	struct Pins {
		char disconnect; ///< Number of pin in the Arduino board to wich it is connected the coil to open the relay.
		char connect_to_L; ///< Number of pin in the Arduino board to wich it is connected the coil to connect the DMM to the "L" lines.
		char connect_to_H; ///< Number of pin in the Arduino board to wich it is connected the coil to connect the DMM to the "H" lines.
	} pins;
	DMMStatus status;
public:
	DMMManager(char H_pin, char L_pin, char disconnect_pin);
	ErrorLogger disconnect();
	ErrorLogger connect_to_L();
	ErrorLogger connect_to_H();
	DMMStatus get_status();
};

#endif
