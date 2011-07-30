/*
 * SerialHandlerIdleState.cpp
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#include "SerialHandlerIdleState.h"
#include "OPhomoProtocolHeader.h"
#include "SerialHandlerConfigState.h"
#include "SerialHandler.h"

namespace OPhomo {

SerialHandlerIdleState::SerialHandlerIdleState(SerialHandler* handler) :  SerialHandlerState(handler) {

}

void SerialHandlerIdleState::handle() {
	LOGLN("Checking in status idle.");
	// We must have one of our COMMANDS
	ASSERT_MIN_LENGTH (2)
	if (readBuffer[0] == 'C' && readBuffer[1] == 'A') {
		// Configuration request.
		// Parse the node id.
		byte destinationNode = 0;
		for (int i = 2; i < *pos; i++) {
			if ('0' <= readBuffer[i] && readBuffer[i] <= '9')
				destinationNode = destinationNode * 10 + readBuffer[i]
						- '0';
			else
				return;
		}
		LOG("Configuring node ");
		Serial.println((int) destinationNode);
		SerialConfigEncoder::transmitter.SetDestinationNode(destinationNode);
//		status = SH_CONFIGURING;
		serialHandler->setHandler(new SerialHandlerConfigState(serialHandler));
	} else {
		ERRORLN("UNKNOWN COMMAND!");
	}
}

SerialHandlerIdleState::~SerialHandlerIdleState() {

}

}
