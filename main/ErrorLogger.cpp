#include "ErrorLogger.h"
#include "RelayParameters.h"

/**
@name ErrorLogger
@note Método constructor.
*/
ErrorLogger::ErrorLogger() {
	error_label = OK;
	error_severity = NO_ERROR;
	reported = false;
	
	pinMode(ERROR_LOGGER_LED_PIN, OUTPUT);
	digitalWrite(ERROR_LOGGER_LED_PIN, LOW);
}

/**
@name ErrorLogger
@note Método constructor por copia de la clase ErrorLogger.
*/
ErrorLogger::ErrorLogger(const ErrorLogger & s) {
	error_label = s.error_label;
	error_severity = s.error_severity;
	reported = s.reported;
}

/**
@name Set
@param _severity: error_severity_t
@param _label: error_label_t
@return void
@note Método que setea un estado.
*/
void ErrorLogger::Set(error_severity_t _severity, error_label_t _label) {
	if (this->reported == false && this->error_severity != NO_ERROR) // This means that there is an error and we are trying to override it.
		this->Report();
	this->error_label = _label;
	this->error_severity = _severity;
	this->reported = false;
	if (_severity != NO_ERROR)
		digitalWrite(ERROR_LOGGER_LED_PIN, HIGH);
	if (_severity == FATAL)
		this->Report();
}

/**
@name Report
@param none
@return void
@note Reports the status of the error through the serial port.
*/
error_severity_t ErrorLogger::Report() {
	switch (this->error_severity) {
		case NO_ERROR:
			Serial.println(F("No error"));
			break;
		case WARNING:
			Serial.print(F("WARNING "));
			Serial.println(error_label_msg[this->error_label]);
			break;
		case ERROR:
			Serial.print(F("ERROR "));
			Serial.println(error_label_msg[this->error_label]);
			digitalWrite(ERROR_LOGGER_LED_PIN, HIGH);
			break;
		case FATAL:
			Serial.print(F("FATAL ERROR "));
			Serial.println(error_label_msg[this->error_label]);
			Serial.println(F("Instrument will be halted for safety."));
			digitalWrite(ERROR_LOGGER_LED_PIN, HIGH);
			while (true) ; // Halt execution.
			break;
	}
	reported = true;
	digitalWrite(ERROR_LOGGER_LED_PIN, LOW);
	return this->error_severity;
}

/**
@name Operador asignacion
@param s: const ErrorLogger &
@return ErrorLogger &
@note Sobrecarga del operador para asignar objetos de la clase ErrorLogger.
*/
ErrorLogger & ErrorLogger::operator=(const ErrorLogger & s) {
	if (this->reported == false && this->error_severity != NO_ERROR)
		this->Report();
	this->Set(s.error_severity, s.error_label);
	//~ error_label = s.error_label;
	//~ error_severity = s.error_severity;
	//~ reported = s.reported;
	return *this;
}
