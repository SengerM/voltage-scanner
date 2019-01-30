#include "RelayModule.h"

RelayModule::RelayModule(ModuleType _module_type, unsigned char * _pins) {
	char i;
	for (i=0; i<MAXIMUM_PINS_PER_MODULE; i++) {
		pins[i] = _pins[i];
		pinMode(pins[i], OUTPUT);
	}
	module_type = _module_type;
	if (module_type == M2C) {
		N_pins = 3;
		N_channels = 2;
	}
	if (module_type == M5C) {
		extern ErrorLogger error_logger;
		error_logger.new_error(Error(FATAL, "Relay module not implemented"));
	}
}

void RelayModule::setup(void) {
	char i;
	for (i=0; i<MAXIMUM_CHANNELS_PER_MODULE; i++)
		used_channels[i] = false; // Mark all channels as 'not used'.
	for (i=0;i<(this->N_channels);i++)
		this->disconnect_channel(i);
}

bool RelayModule::request_channel(unsigned char channel_number_in_relay_module) {
	if (channel_number_in_relay_module >= this->N_channels) // The channel has not such channel!
		return false;
	if (this->used_channels[channel_number_in_relay_module] == false) { // This means the channel is free to use.
		this->used_channels[channel_number_in_relay_module] = true;
		return true;
	} else // This means the channel is already ocupied.
		return false;
}

bool RelayModule::connect_channel_to_line(LineLabels line, unsigned char channel) {
	switch (this->module_type) { // The action to take deppends on the module_type (hardware).
		case M2C: {
			if (line == A) {
				if (channel == 0) 
					this->M2C_generate_signal(ch0_to_line_a);
				else if (channel == 1)
					this->M2C_generate_signal(ch1_to_line_a);
				else
					return false;
			} else if (line == B) {
				if (channel == 0)
					this->M2C_generate_signal(ch0_to_line_b);
				else if (channel == 1)
					this->M2C_generate_signal(ch1_to_line_b);
				else
					return false;
			} else
				return false;
		} break;
		default: break;
	}
}

bool RelayModule::disconnect_channel(unsigned char channel) {
	switch (this->module_type) { // The action to take deppends on the module_type (hardware).
		case M2C: {
			if (channel == 0)
				this->M2C_generate_signal(ch0_disconnect);
			else if (channel == 1)
				this->M2C_generate_signal(ch1_disconnect);
		} break;
		default: break;
	}
}

void RelayModule::M2C_generate_signal(M2C_signals signal) {
	int k;
	M2C_signals standby_signal = standby;
	for (k=0; k<this->N_pins; k++)
		digitalWrite(this->pins[k], (signal & (1<<k)) ? LOW : HIGH);
	delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
	for (k=0; k<this->N_pins; k++)
		digitalWrite(this->pins[k], (standby_signal & (1<<k)) ? LOW : HIGH);
	delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
}
