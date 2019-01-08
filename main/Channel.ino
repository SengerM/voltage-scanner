#include "Channel.h"

Channel::Channel(RelayModule * _relay_module, unsigned char _channel_number_in_relay_module) {
	relay_module = _relay_module;
	if (_relay_module->request_channel(_channel_number_in_relay_module) == true) // Check if the channel is available.
		channel_number_in_relay_module = _channel_number_in_relay_module;
	else { // In case the channel is not available, indicate error and halt execution.
		ErrorLogger error_logger;
		error_logger.Set(FATAL, ERROR_FATAL_Channel_INVALID_CHANNEL_NUMBER_FOR_THIS_RELAY_MODULE);
		error_logger.Report();
	}
}

RelayModule * Channel::get_relay_module() {
	return this->relay_module;
}

unsigned char Channel::get_channel_number_in_relay_module() {
	return this->channel_number_in_relay_module;
}
