#include "main.h"

SerialCommand SCmd;
RelayModule module_1(M2C, M2C_MODULE_PINS); // This is the physical board in which the channels are implemented.
Channel channels[N_CHANNELS] = {Channel(&module_1, 0), Channel(&module_1, 1)}; // The channels.
DMMManager DMMm(CONNECT_DMM_TO_H_PIN, CONNECT_DMM_TO_L_PIN, DISCONNECT_DMM_PIN); // Digital multimeter.
LineManager LM(LINE_A_STATUS_PIN, LINE_B_STATUS_PIN, CONNECT_STATUS_DETECTOR_PIN, DISCONNECT_STATUS_DETECTOR_PIN, DMMm);
ErrorLogger error_logger(ERROR_LOGGER_LED_PIN, ERROR_LOGGER_BUZZER_PIN);

void setup() {
	Serial.begin(9600);
	for (int i; i<sizeof(commands_strings)/sizeof(commands_strings[0]); i++) // Add the commands to the command handler.
		SCmd.addCommand(commands_strings[i], commands_functions[i]);
	SCmd.setDefaultHandler(unknown_cmd);
	module_1.setup();
	DMMm.setup();
	LM.setup();
}

void loop() {
	SCmd.readSerial();
}

// SerialCommand functions ---------------------------------------------

void unknown_cmd(void) {
	error_logger.new_error(Error(ERROR, "Unknown command"));
}

void idn_cmd(void) {
	Serial.print(F(IDN));
	Serial.print(LINE_TERMINATION);
}

void version_cmd(void) {
	Serial.print(F("Software compilation timestamp: "));
	Serial.print(F(COMPILATION_TIMESTAMP));
	Serial.print(LINE_TERMINATION);
}

void errors_cmd(void) {
	error_logger.report_all_errors();
}

void connect_cmd(void) {
	extern SerialCommand SCmd;
	extern Channel channels[N_CHANNELS];
	unsigned int channel_number;
	LineLabels line;
	char * arg1, * arg2;
	
	arg1 = SCmd.next(); 
	arg2 = SCmd.next();
	if (arg1 == NULL || arg2 == NULL) {
		error_logger.new_error(Error(ERROR, "Missing arguments"));
		return;
	}
	channel_number = atoi(arg1);
	if (channel_number > N_CHANNELS || channel_number < 0) {
		error_logger.new_error(Error(ERROR, "Invalid channel"));
		return;
	}
	if (arg2[0] == 'A')
		line = A;
	else if (arg2[0] == 'B')
		line = B;
	else {
		error_logger.new_error(Error(ERROR, "Invalid line"));
		return;
	}
	if (channel_number == 0)
		LM.open_line(line);
	else
		LM.connect_channel(channels[channel_number-1], line);
}

void dmm_cmd(void) {
	extern SerialCommand SCmd;
	char * arg;
	
	arg = SCmd.next(); 
	if (arg == NULL) {
		error_logger.new_error(Error(ERROR, "Missing argument"));
		return;
	}
	switch (arg[0]) {
		case 'H': DMMm.connect_to_H(); break;
		case 'L': DMMm.connect_to_L(); break;
		case 'D': DMMm.disconnect(); break;
	}
}
// ---------------------------------------------------------------------
