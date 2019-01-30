#ifndef _RELAY_MODULE_
#define _RELAY_MODULE_

#include <Arduino.h>
#include "ErrorLogger.h"
#include "RelayParameters.h"
#include "Types.h"
#include "Delay.h"

#define MAXIMUM_PINS_PER_MODULE 4
#define MAXIMUM_CHANNELS_PER_MODULE 5

enum ModuleType {M2C, M5C}; ///< Each of this labels is a specific code that identifies a specific piece of hardware.

enum M2C_signals {
	ch0_disconnect = 0,
	ch1_disconnect = 1,
	ch0_to_line_a = 2,
	ch1_to_line_a = 4,
	ch0_to_line_b = 5,
	ch1_to_line_b = 3,
	standby = 6
}; ///< Binary encoded signals used to control the relays in the module 'M2C'.

class RelayModule {
private:
	unsigned char pins[MAXIMUM_PINS_PER_MODULE]; ///< Physical pins to wich the module is connected in the Arduino board.
	ModuleType module_type; ///< This defines which hardware is being used.
	unsigned char N_pins; ///< Number of pins the module uses (depends ond the 'module_type').
	unsigned char N_channels; ///< Number of channels the module has (depends on the 'module_type').
	bool used_channels[MAXIMUM_CHANNELS_PER_MODULE]; ///< This array initializes to 'false' and takes a register of which channels are already in use. Just for safety when configuring the system.
	
	void M2C_generate_signal(M2C_signals signal); ///< This method is used to generate the output signals to command the relays.
public:
	RelayModule(ModuleType module_type, unsigned char * pins); ///< The creator.
	bool request_channel(unsigned char channel_number_in_relay_module); ///< Checks whether a channel was already configured or not within the current RelayModule object. If it is free for use, returns 'true' and makrs it as used. Otherwise returns 'false' indicating it is ocupied.
	bool connect_channel_to_line(LineLabels line, unsigned char channel); ///< Acts on the pins of the Arduino borad in order to connect the specified channel to the specified line.
	bool disconnect_channel(unsigned char channel); ///< Acts on the pins of the Arduino board in order to disconnect the specified channel.
	void setup(void);
};

#endif
