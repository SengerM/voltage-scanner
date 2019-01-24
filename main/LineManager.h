#ifndef _LINE_MANAGER_H_
#define _LINE_MANAGER_H_

#include <Arduino.h>
#include "Channel.h"
#include "RelayModule.h"
#include "ErrorLogger.h"
#include "RelayParameters.h"
#include "Types.h"
#include "DMMManager.h"
#include "Delay.h"

class LineManager {
private:
	Channel * currently_connected_channel[2]; ///< When a channel is connected, it is stored here. When no channel is connected this pointer is null. This must be invoked as "currently_connected_channel[A]" or "currently_connected_channel[B]", see the definition of "LineLabels".
	LineStatus line_status[2];
	DMMManager * DMM_manager; ///< The DMMManager object must be stored here.
	struct Pins {
		char read_detector[2]; ///< Number of pin in the Arduino board to wich it is connected the circuit to check the line status.
		char connect_detectors; ///< Number of pin in the Arduino board to wich it is connected the coil to close the relay.
		char disconnect_detectors; ///< Number of pin in the Arduino board to wich it is connected the coil to open the relay.
	} pins;
public:
	LineManager(char read_detector_A_pin, char read_detector_B_pin, char connect_detectors_pin, char disconnect_detectors_pin, DMMManager & DMM_manager); ///< Constructor. Needs specification for the pins to drive the hardware to check the status of the line.
	void connect_channel(Channel & channel, LineLabels line); ///< Connect the specified channel to the specified line.
	void open_line(LineLabels line); ///< Disconnect any channel that could be connected to the line.
	LineStatus check_line_status(LineLabels line); ///< Checks whether there is anything connected to the line and returns the status.
};

#endif
