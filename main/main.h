#ifndef _MAIN_H_
#define _MAIN_H_

#include "Channel.h"
#include "RelayModule.h"
#include "LineManager.h"
#include "DMMManager.h"
#include "SerialCommand.h"
#include "ErrorLogger.h"
#include "Common.h"
#include "ArduinoPins.h"
#include "Delay.h"

#define N_CHANNELS 2

#define COMPILATION_TIMESTAMP __DATE__ " " __TIME__
#define FIRMWARE_VERSION "2.1"
#define IDN "Zener Scanner INTI"


void unknown_cmd(void);
void idn_cmd(void);
void version_cmd(void);
void errors_cmd(void);
void connect_cmd(void);
void open_line_cmd(void);
void dmm_cmd(void);

char commands_strings[][SERIALCOMMAND_MAXCOMMANDLENGTH] = {
	"IDN?", // Returns the identity of the instrument.
	"VERSION?", // Returns information about the firmware.
	"ERRORS?", // Queries all the errors in the error_logger.
	"E?", // Same as "ERRORS?".
	"CONNECT", // CONNECT <ch> <line>, <ch> must be a number (0,1,2,...) and <line> must be 'A' or 'B'. (0 disconnects the line.)
	"C", // Same as "CONNECT".
	"DMM", // DMM <option>, <option> can be 'H' (high), 'L' (low) or 'D' (disconnect).
	"OPENLINE", // OPENLINE <line>, <line> must be 'A' or 'B'. If no argument is passed, both lines are disconnected.
	"OL" // Same as "OPENLINE".
};

void * commands_functions[] = {
	idn_cmd,
	version_cmd,
	errors_cmd,
	errors_cmd,
	connect_cmd,
	connect_cmd,
	dmm_cmd,
	open_line_cmd,
	open_line_cmd
};

#endif
