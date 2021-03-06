/*
 * RF12Concatenator.cpp
 *
 *  Created on: 5 Jul 2011
 *      Author: decock
 */

#include "RF12Concatenator.h"
#include "OPhomoProtocolHeader.h"
#include "HardwareSerial.h"

namespace OPhomo {

RF12Concatenator::RF12Concatenator(RF12Module* rf12) {
	rf12Module = rf12;
	pos = 1;
}

RF12Concatenator::RF12Concatenator() {
	pos = 1;
}

void RF12Concatenator::SetDestinationNode(byte nodeId) {
	destination = nodeId;
}

/**
 * This sets the type of the message.
 */
void RF12Concatenator::SetMessageType(byte type) {
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) buffer;
	header->MessageType = type;
}

/**
 * This will add a configuration part and send it if the message is full.
 */
void RF12Concatenator::Send(byte* newPart, byte length) {
	if (length > RF12_MAXDATA - 1) {
		// Drop this part, it is too long.
//		ERRORLN("ERROR, config too long.");
		return;
	}
	if (pos + length > RF12_MAXDATA) {
		// We first need to send the current config.
		this->SendPartNow();
		pos = 1;
	}
	memcpy(buffer + pos, newPart, length);
	pos += length;
}

/**
 * This will send the last part of a configuration.
 */
void RF12Concatenator::LastPartSend() {
	// We end with a 0 option.
	//DEBUG("LPS::Pos:");
	//DEBUGLN((int)pos);
	buffer[pos++] = 0;
	buffer[pos++] = 0;
	this->SendPartNow();
	pos = 1;
}

void RF12Concatenator::SendPartNow() {
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) buffer;
	//	header->MessageType = type;
	header->SourceNode = rf12Module->getNodeId();
	// Send
	bool result = false;
	uint8_t maxretries = 8;
	while(!result && maxretries--) {
		result = rf12Module->Send(destination, buffer, pos, 0 /*false*/);
		if ( !result ) {
			Serial.print("Can't send on RF12: length ");
			Serial.println(pos);
			delay(200);
		}

	}
}

RF12Concatenator::~RF12Concatenator() {
}

}
