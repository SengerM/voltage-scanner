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

#define N_CHANNELS 2


#define IDN "INTI Scanner 190108"

void unknown_cmd(void);
void idn_cmd(void);
void connect_cmd(void);
void dmm_cmd(void);

char commands_strings[][SERIALCOMMAND_MAXCOMMANDLENGTH] = {
	"IDN?",
	"CONNECT",
	"DMM"
};

void * commands_functions[] = {
	idn_cmd,
	connect_cmd,
	dmm_cmd
};

#endif
