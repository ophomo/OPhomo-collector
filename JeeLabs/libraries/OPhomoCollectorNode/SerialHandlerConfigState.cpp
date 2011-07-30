/*
 * SerialHandlerConfigState.cpp
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#include "SerialHandlerConfigState.h"
#include "SerialHandlerIdleState.h"
#include "OPhomoProtocolHeader.h"
#include "SerialHandler.h"

namespace OPhomo {

SerialHandlerConfigState::~SerialHandlerConfigState() {

}

void SerialHandlerConfigState::handle() {
	LOGLN("Checking in status configuring");
	// First trim spaces and tabs.
	byte start;
	for (start = 0; start < *pos; start++) {
		if (!(readBuffer[start] == 0x20 || readBuffer[start] == 0x9)) {
			break;
		}
	}
	ASSERT_MIN_LENGTH(start + 2)
	// Check if we are ending the configuration.
	if (*pos >= (start + 3) && readBuffer[start] == '/' && readBuffer[start
			+ 1] == 'C' && readBuffer[start + 2] == 'A') {
		SerialConfigEncoder::transmitter.LastPartSend();
		LOGLN("Finished configuration.");
		serialHandler->setHandler(new SerialHandlerIdleState(serialHandler));
		return;
	}
	for (byte i = 0; i < this->encoderSize; i++) {
		// See if any of the
		if (memcmp(readBuffer + start, encoders[i].type, 4) == 0) {
			// Cool, we have the matching encoder.
			encoders[i].encoder->Handle(readBuffer + start + 5, pos - start
					- 5);
			LOGLN("Handled by Encoder !");
			// Done
			return;
		}
	}
	// If we reach this part of the code, no encoder was found.
	ERRORLN("No Encoder found !");
}

}

SerialHandlerConfigState::SerialHandlerConfigState(SerialHandler* handler): serialHandlerState(handler) {
	// TODO Auto-generated constructor stub

}

}
