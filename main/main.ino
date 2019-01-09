#include "main.h"

SerialCommand SCmd;
RelayModule module_1(M2C, M2C_MODULE_PINS); // This is the physical board in which the channels are implemented.
Channel channels[N_CHANNELS] = {Channel(&module_1, 0), Channel(&module_1, 1)}; // The channels.
DMMManager DMMm(CONNECT_DMM_TO_H_PIN, CONNECT_DMM_TO_L_PIN, DISCONNECT_DMM_PIN); // Digital multimeter.
LineManager LM(LINE_A_STATUS_PIN, LINE_B_STATUS_PIN, CONNECT_STATUS_DETECTOR_PIN, DISCONNECT_STATUS_DETECTOR_PIN, DMMm);

void setup() {
	Serial.begin(9600);
	for (int i; i<sizeof(commands_strings)/sizeof(commands_strings[0]); i++)
		SCmd.addCommand(commands_strings[i], commands_functions[i]); ///< Returns a string identifying the instrument
	SCmd.setDefaultHandler(unknown_cmd);
}

void loop() {
	SCmd.readSerial();
	//~ // ------------------------------
	//~ LM_err = LM.connect_channel(channel_1, A);
	//~ LM_err = LM.connect_channel(channel_2, B);
	//~ DMM_err = DMMm.connect_to_H();
	
	//~ while (true) {
		//~ command = readCommand();
		//~ switch (command) {
			//~ case 'A':
				//~ LM_err = LM.connect_channel(channel_1, A);
				//~ break;
			//~ case 'B':
				//~ LM_err = LM.connect_channel(channel_2, B);
				//~ break;
			//~ case 'C':
				//~ LM_err = LM.open_line(A);
				//~ break;
			//~ case 'D':
				//~ LM_err = LM.open_line(B);
			//~ case 'E':
				//~ DMM_err = DMMm.connect_to_H();
				//~ break;
			//~ case 'F':
				//~ DMM_err = DMMm.connect_to_L();
				//~ break;
			//~ case 'G':
				//~ DMM_err = DMMm.disconnect();
		//~ }
		//~ LM_err.Report();
		//~ DMM_err.Report();
	//~ }
}

// SerialCommand functions ---------------------------------------------

void unknown_cmd(void) {
	Serial.print(F("Unknown command"));
	Serial.print(LINE_TERMINATION);
}

void idn_cmd(void) {
	Serial.print(F(IDN));
	Serial.print(LINE_TERMINATION);
}

void connect_cmd(void) {
	extern SerialCommand SCmd;
	unsigned int channel_number;
	LineLabels line;
	char * arg1, * arg2;
	
	arg1 = SCmd.next(); 
	arg2 = SCmd.next();
	if (arg1 == NULL || arg2 == NULL) {
		Serial.print(F("Missing arguments"));
		Serial.print(LINE_TERMINATION);
		return;
	}
	channel_number = atoi(arg1);
	if (channel_number > N_CHANNELS) {
		Serial.print(F("Invalid channel"));
		Serial.print(LINE_TERMINATION);
		return;
	}
	if (arg2[0] == 'A')
		line = A;
	else if (arg2[0] == 'B')
		line = B;
	else {
		Serial.print(F("Invalid line"));
		Serial.print(LINE_TERMINATION);
		return;
	}
	
	ErrorLogger LM_err = LM.connect_channel(channels[channel_number], line);
}

void dmm_cmd(void) {
	extern SerialCommand SCmd;
	char * arg;
	
	//~ arg = SCmd.next();
	Serial.print("Not yet implemented");
	Serial.print(LINE_TERMINATION);
}
// ---------------------------------------------------------------------
