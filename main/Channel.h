#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "RelayModule.h"
#include "ErrorLogger.h"

class Channel {
private:
	RelayModule * relay_module; ///< Pointer to a RelayModule objet to wich the channel physically belongs.
	unsigned char channel_number_in_relay_module; ///< Number of channel in the RelayModule object to wich the channel belongs. The numeration goes from 0 to N-1.
public:
	Channel(RelayModule * relay_module, unsigned char channel_number_in_relay_module); ///< Constructor.
	RelayModule * get_relay_module(); ///< Returns a pointer to the RelayModule object to wich the channel physically belongs.
	unsigned char get_channel_number_in_relay_module(); ///< Returns the value of the channel number in the relay module.
};

#endif
