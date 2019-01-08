#ifndef _MAIN_H_
#define _MAIN_H_

#include "Channel.h"
#include "RelayModule.h"
#include "LineManager.h"
#include "DMMManager.h"
#include "SerialCommand.h"
#include "ErrorLogger.h"

#define N_CHANNELS 2

#define LINE_TERMINATION '\n'
#define IDN "INTI Scanner 190108"

void idn_cmd(void);
void unknown_cmd(void);
void connect_cmd(void);

char commands_strings[][SERIALCOMMAND_MAXCOMMANDLENGTH] = {
	"IDN?",
	"CONNECT"
};

void * commands_functions[] = {
	idn_cmd,
	connect_cmd
};

#endif
