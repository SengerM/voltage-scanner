#include "DMMManager.h"

DMMManager::DMMManager(char H_pin, char L_pin, char disconnect_pin) {
	this->pins.connect_to_H = H_pin;
	this->pins.connect_to_L = L_pin;
	this->pins.disconnect = disconnect_pin;
	this->status = connected_to_H;
}

void DMMManager::setup(void) {
	pinMode(this->pins.connect_to_H, OUTPUT);
	pinMode(this->pins.connect_to_L, OUTPUT);
	pinMode(this->pins.disconnect, OUTPUT);
	this->disconnect();
}

void DMMManager::disconnect() {
	if (this->status != disconnected) {
		digitalWrite(this->pins.disconnect, HIGH);
		delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
		digitalWrite(this->pins.disconnect, LOW);
		delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
		this->status = disconnected;
	}
}

void DMMManager::connect_to_L() {
	if (this->status != connected_to_L) {
		this->disconnect();
		digitalWrite(this->pins.connect_to_L, HIGH);
		delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
		digitalWrite(this->pins.connect_to_L, LOW);
		delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
		this->status = connected_to_L;
	}
}

void DMMManager::connect_to_H() {
	if (this->status != connected_to_H) {
		this->disconnect();
		digitalWrite(this->pins.connect_to_H, HIGH);
		delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
		digitalWrite(this->pins.connect_to_H, LOW);
		delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
		this->status = connected_to_H;
	}
}

DMMStatus DMMManager::get_status() {
	return this->status;
}
