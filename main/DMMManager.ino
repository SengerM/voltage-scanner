#include "DMMManager.h"

DMMManager::DMMManager(char H_pin, char L_pin, char disconnect_pin) {
	this->pins.connect_to_H = H_pin;
	this->pins.connect_to_L = L_pin;
	this->pins.disconnect = disconnect_pin;
	
	pinMode(H_pin, OUTPUT);
	pinMode(L_pin, OUTPUT);
	pinMode(disconnect_pin, OUTPUT);
	
	this->disconnect();
}

ErrorLogger DMMManager::disconnect() {
	ErrorLogger err;
	if (this->status != disconnected) {
		digitalWrite(this->pins.disconnect, HIGH);
		delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
		digitalWrite(this->pins.disconnect, LOW);
		delay_milliseconds(RELAY_COMMUTATION_TIME_MS);
		this->status = disconnected;
	}
	return err;
}

ErrorLogger DMMManager::connect_to_L() {
	ErrorLogger err;
	if (this->status != connected_to_L) {
		this->disconnect();
		digitalWrite(this->pins.connect_to_L, HIGH);
		delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
		digitalWrite(this->pins.connect_to_L, LOW);
		this->status = connected_to_L;
	}
	return err;
}

ErrorLogger DMMManager::connect_to_H() {
	ErrorLogger err;
	if (this->status != connected_to_H) {
		this->disconnect();
		digitalWrite(this->pins.connect_to_H, HIGH);
		delay_milliseconds(RELAY_COIL_PULSE_TIME_MS);
		digitalWrite(this->pins.connect_to_H, LOW);
		this->status = connected_to_H;
	}
	return err;
}

DMMStatus DMMManager::get_status() {
	return this->status;
}
