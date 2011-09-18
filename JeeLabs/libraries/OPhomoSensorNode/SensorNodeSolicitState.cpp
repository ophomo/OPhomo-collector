/*
 * SensorNodeSolicitState.cpp
 *
 *  Created on: 27 Jul 2011
 *      Author: decock
 */

#include "SensorNodeSolicitState.h"
#include "OPhomoProtocolHeader.h"
#include "SensorNode.h"
#include "ConfigurationController.h"
#include "SensorNodeConfigAcceptState.h"
namespace OPhomo {

SensorNodeSolicitState::SensorNodeSolicitState(SensorNode* inNode) :
	SensorNodeState(inNode) {
	INFOLN("<SOL>");
}

void SensorNodeSolicitState::handleMessage(byte* message, byte length) {
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) (message
			+ RF12_HDR_SIZE);
	byte pos = RF12_HDR_SIZE + sizeof(OPhomoProtocolHeader);
	bool handled;
	// This is probably a config message ?
	if (header->MessageType == CONFIG_ADVERTISE_TYPE) {
		INFOLN((int)length);
		while (1) {
			// ASSERT LENGTH
			handled = false;
			if (message[pos] == 0 && message[pos + 1] == 0) {
				// We reached the end of the configuration.
				// Change the state handler and go!
				data->collectorNodeId = header->SourceNode;
				node->setStateHandler(new SensorNodeConfigAcceptState(node));
				return;
			}
			for (byte controllerIndex = 0; controllerIndex
					< data->controllersSize; controllerIndex++) {
				if (message[pos]
						== data->controllers[controllerIndex]->getType()) {
					if ((data->controllers[controllerIndex]->HandleConfig(
							message + pos + 2, message[pos + 1]) == 0))
						return;
					handled = true;
					break;
				}
			}
			if (!handled) {
				return;
			}
			pos += 2 + message[pos + 1];
			if (pos >= length  ) {
				break;
			}
		}
	}
}

void SensorNodeSolicitState::tick() {
	if (data->timer.idle()) {
		SolicitConfig();
		data->timer.set(5000);
	}
}

void SensorNodeSolicitState::SolicitConfig() {
	RF12Module* rf12 = getRF12Module();
	// Configure the message.
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) data->message;
	header->MessageType = CONFIG_SOLICIT_TYPE;
	header->SourceNode = rf12->getNodeId();
	// Send
	rf12->Send((byte) 0, data->message, (uint8_t) CONFIG_SOLICIT_LENGTH, 0 /*false*/);
}

SensorNodeSolicitState::~SensorNodeSolicitState() {
}

}
