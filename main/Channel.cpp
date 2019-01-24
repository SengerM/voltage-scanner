#include "Channel.h"

Channel::Channel(RelayModule * _relay_module, unsigned char _channel_number_in_relay_module) {
	this->relay_module = _relay_module;
	if (_relay_module->request_channel(_channel_number_in_relay_module) == true) // Check if the channel is available.
		this->channel_number_in_relay_module = _channel_number_in_relay_module;
	else { // In case the channel is not available, indicate error and halt execution.
		extern ErrorLogger error_logger;
		error_logger.new_error(Error(FATAL, "Cannot configure channel"));
	}
}

RelayModule * Channel::get_relay_module() {
	return this->relay_module;
}

unsigned char Channel::get_channel_number_in_relay_module() {
	return this->channel_number_in_relay_module;
}
