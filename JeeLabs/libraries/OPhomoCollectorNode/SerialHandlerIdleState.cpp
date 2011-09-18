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
INFOLN("<IDLE>")
}

void SerialHandlerIdleState::handle() {
//	LOGLN("Checking in status idle.");
	// We must have one of our COMMANDS
	ASSERT_MIN_LENGTH (2)
	if (data->readBuffer[0] == 'C' && data->readBuffer[1] == 'A') {
		// Configuration request.
		// Parse the node id.
		byte destinationNode = 0;
		for (int i = 2; i < data->pos; i++) {
			if ('0' <= data->readBuffer[i] && data->readBuffer[i] <= '9')
				destinationNode = destinationNode * 10 + data->readBuffer[i]
						- '0';
			else
				return;
		}
//		LOG("Configuring node ");
//		Serial.println((int) destinationNode);
		SerialConfigEncoder::transmitter.SetDestinationNode(destinationNode);
		SerialConfigEncoder::transmitter.SetMessageType(CONFIG_ADVERTISE_TYPE);
		serialHandler->setHandler(new SerialHandlerConfigState(serialHandler));
	} else if (data->readBuffer[0] == 'C' && data->readBuffer[1] == 'O') {
		// Configuration Acknowledgement
		byte destinationNode = 0;
		for (int i = 2; i < data->pos; i++) {
			if ('0' <= data->readBuffer[i] && data->readBuffer[i] <= '9')
				destinationNode = destinationNode * 10 + data->readBuffer[i]
						- '0';
			else
				return;
		}
		SerialConfigEncoder::transmitter.SetDestinationNode(destinationNode);
		SerialConfigEncoder::transmitter.SetMessageType(CONFIG_ACK_TYPE);
		SerialConfigEncoder::transmitter.LastPartSend();
	} else {
		ERRORLN("IDLE:UNKNOWN COMMAND!");
	}
}

SerialHandlerIdleState::~SerialHandlerIdleState() {

}

}
