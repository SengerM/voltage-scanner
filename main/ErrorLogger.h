#ifndef _STATUS_H_
#define _STATUS_H_

#include <Arduino.h>
#include "ArduinoPins.h"

typedef enum { // Asocia etiquetas a los posibles errores que puedan aparecer, así los podemos identificar.
	OK = 0,
	ERROR_FATAL_LineManager_CANNOT_CREATE = 1,
	ERROR_LineManager_CANNOT_OPEN_LINE = 2,
	WARNING_LineManager_TRYING_TO_CONNECT_CHANNEL_TO_BUSSY_LINE = 3,
	ERROR_FATAL_RelayModule_MODULE_NOT_IMPLEMENTED=4,
	ERROR_FATAL_Channel_INVALID_CHANNEL_NUMBER_FOR_THIS_RELAY_MODULE=5,
	ERROR_LineManager_CANNOT_CONNECT_LINE=6,
} error_label_t;

static const char* error_label_msg[] = { // El orden de estas cadenas debe estar correctamente asociado con el valor de las etiquetas de «error_label_t».
	"No error",
	"1: cannot create LineManager object with a label different to 'A' or 'B'",
	"2: cannot open line",
	"3: trying to connect channel to a line which already has a channel connected",
	"4: RelayModule not implemented",
	"5: cannot create Channel object, invalid channel number or already in use",
	"6: cannot connect line",
};

typedef enum {
	NO_ERROR = 0,
	WARNING = 1,
	ERROR = 2,
	FATAL = 3
} error_severity_t;

class ErrorLogger {
private:
	error_label_t error_label; // Acá se guarda la etiqueta que indica de qué tipo de error se trata.
	error_severity_t error_severity; // Acá se guarda una etiqueta que indica la severidad del error.
	bool reported; ///< If this is 'false' then the error was not reported yet (just registered). If 'true' the error was already reported.
public:
	ErrorLogger(); ///< Constructor.
	ErrorLogger(const ErrorLogger &); ///< Copy constructor.
	void Set(error_severity_t error_severity, error_label_t error_label); ///< Set an error.
	
	error_severity_t Report(); ///< Reports the complete error type and message.
	
	ErrorLogger & operator=(const ErrorLogger& s);
};

#endif
