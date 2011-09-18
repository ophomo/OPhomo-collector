/*
 * SensorNodeConfigAcceptState.cpp
 *
 *  Created on: 27 Jul 2011
 *      Author: decock
 */

#include "SensorNodeConfigAcceptState.h"
#include "ConfigurationController.h"
#include "SensorNodeActiveState.h"
namespace OPhomo {

SensorNodeConfigAcceptState::SensorNodeConfigAcceptState(SensorNode* inNode) :
	SensorNodeState(inNode) {
	INFOLN("<ACCEPT>");
	sendAccept();
}

void SensorNodeConfigAcceptState::handleMessage(byte* message, byte length) {
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) (message
			+ RF12_HDR_SIZE);
	// This is probably a config message ?
	if (header->MessageType == CONFIG_ACK_TYPE) {
		node->setStateHandler(new SensorNodeActiveState(node));
		return;
	} else {
		INFO("Ignoring message type");
		INFOLN(header->MessageType);
	}
}

void SensorNodeConfigAcceptState::tick() {
	if (data->timer.idle()) {
		sendAccept();
		data->timer.set(5000);
	}
}

void SensorNodeConfigAcceptState::sendAccept() {
	// Walk the controllers and send the result.
	node->rf12Transmitter.SetMessageType(CONFIG_ACCEPT_TYPE);
	for (byte controllerIndex = 0; controllerIndex < data->controllersSize; controllerIndex++) {
		data->controllers[controllerIndex]->ConfigReply();
	}
	node->rf12Transmitter.LastPartSend();
}

SensorNodeConfigAcceptState::~SensorNodeConfigAcceptState() {
	// TODO Auto-generated destructor stub
}

}
