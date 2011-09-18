/*
 * SerialHandler.cpp
 *
 *  Created on: Feb 21, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "SerialHandler.h"
#include "OPhomoProtocolHeader.h"
#include "SerialHandlerIdleState.h"
#include "log.h"
#define SH_IDLE 0
#define SH_CONFIGURING 1


namespace OPhomo {

SerialHandler::SerialHandler() {
	// TODO Auto-generated constructor stub
	data.pos = 0;
//	data.status = SH_IDLE;
	// Currently, we support just 5.
	data.encoders = new ConfigEncoderMapping[5];
	data.encoderSize = 0;
	state = new SerialHandlerIdleState(this);
}

void SerialHandler::Try() {
	if (Serial.available()) {
		data.readBuffer[data.pos] = Serial.read();
		if (data.readBuffer[data.pos] == (byte) 0x0D) {
			// Handle the command.
			if (state)
				state->handle();
			data.pos = 0;
		} else {
			if ((unsigned char) data.pos < (SERIAL_BUFFER_SIZE - 1)) {
				data.pos++;
			} else {
				ERRORLN("BUFFER FULL");
				data.pos = 0;
			}
		}
	}
}

SerialHandler::~SerialHandler() {
	// TODO Auto-generated destructor stub
}

void SerialHandler::setHandler( SerialHandlerState* newState ) {
	if ( state )
		delete state;
	state = newState;
}

void SerialHandler::RegisterEncoder(const byte* type,
		SerialConfigEncoder* encoder) {
	if (data.encoderSize == 5) {
		ERRORLN("Only space for 5 encoders is reserved. Add more space in the SerialHandler.");
		return;
	} else {
		data.encoders[data.encoderSize].type = type;
		data.encoders[data.encoderSize++].encoder = encoder;
	}

}

}
