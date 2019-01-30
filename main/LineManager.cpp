#include "LineManager.h"

LineManager::LineManager(char read_detector_A_pin, char read_detector_B_pin, char connect_detectors_pin, char disconnect_detectors_pin, DMMManager & DMM_manager_) {
	this->pins.read_detector[A] = read_detector_A_pin;
	this->pins.read_detector[B] = read_detector_B_pin;
	this->pins.connect_detectors = connect_detectors_pin;
	this->pins.disconnect_detectors = disconnect_detectors_pin;
	
	this->DMM_manager = &DMM_manager_;
	
	currently_connected_channel[0] = NULL;
	currently_connected_channel[1] = NULL;
}

void LineManager::setup(void) {
	pinMode(this->pins.read_detector[A], INPUT);
	pinMode(this->pins.read_detector[B], INPUT);
	pinMode(this->pins.connect_detectors, OUTPUT);
	pinMode(this->pins.disconnect_detectors, OUTPUT);
}

void LineManager::connect_channel(Channel & channel, LineLabels line) {
	extern ErrorLogger error_logger;
	if (this->check_line_status(line) == open) {
		channel.get_relay_module()->connect_channel_to_line(line, channel.get_channel_number_in_relay_module());
		delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
		if (this->check_line_status(line) == connected) // If the connection was succesfull...
			this->currently_connected_channel[line] = &channel;
		else
			error_logger.new_error(Error(ERROR, "Cannot connect line"));
	} else {
		error_logger.new_error(Error(WARNING, "Trying to connect channel to bussy line"));
	}
}

void LineManager::open_line(LineLabels line) {
	extern ErrorLogger error_logger;
	if (this->check_line_status(line) == open) // if (there is nothing connected) do nothing.
		this->currently_connected_channel[line] = NULL;
	else { // There is something connected.
		if (this->currently_connected_channel[line] != NULL) { // If we know which channel is connected...
			this->currently_connected_channel[line]->get_relay_module()->disconnect_channel(this->currently_connected_channel[line]->get_channel_number_in_relay_module());
			delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
			if (this->check_line_status(line) == open) { // Check if effectively disconected the channel.
				this->currently_connected_channel[line] = NULL;
			}
		} else // There is something connected but we don't know which channel!!! This is an error!
			error_logger.new_error(Error(ERROR, "Cannot open line"));
	}
}

LineStatus LineManager::check_line_status(LineLabels line) {
	LineStatus status;
	DMMStatus current_DMM_status = this->DMM_manager->get_status();
	if (current_DMM_status != disconnected)
		this->DMM_manager->disconnect();
	// Connect detection system -------
	digitalWrite(this->pins.connect_detectors, HIGH);
	delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
	digitalWrite(this->pins.connect_detectors, LOW);
	delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
	// Read status --------------------
	if (digitalRead(this->pins.read_detector[line]))
		status = open;
	else
		status = connected;
	this->line_status[line] = status;
	// Disconnect detection system ----
	digitalWrite(this->pins.disconnect_detectors, HIGH);
	delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
	digitalWrite(this->pins.disconnect_detectors, LOW);
	delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
	// Connect DMM back again ---------
	if (current_DMM_status == connected_to_H)
		this->DMM_manager->connect_to_H();
	if (current_DMM_status == connected_to_L)
		this->DMM_manager->connect_to_L();
	return status;
}
