/*
 * SensorNodeSollicitState.cpp
 *
 *  Created on: 27 Jul 2011
 *      Author: decock
 */

#include "SensorNodeSollicitState.h"
#include "OPhomoProtocolHeader.h"
#include "SensorNode.h"
#include "ConfigurationController.h"
#include "SensorNodeConfigAcceptState.h"
namespace OPhomo {

SensorNodeSollicitState::SensorNodeSollicitState(SensorNode* inNode) :
	SensorNodeState(inNode) {

}

void SensorNodeSollicitState::handleMessage(byte* message, byte length) {
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) (message
			+ RF12_HDR_SIZE);
	byte pos = RF12_HDR_SIZE + sizeof(OPhomoProtocolHeader);
	bool handled;
	// This is probably a config message ?
	if (header->MessageType == CONFIG_ADVERTISE_TYPE) {
		while (1) {
			// ASSERT LENGTH
			Serial.print("Checking message type : ");
			Serial.print((int) message[pos]);
			Serial.print(" with length ");
			Serial.println((int) message[pos + 1]);
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
					Serial.print(
							"Found controller, handling message with size ");
					Serial.println((int) message[pos + 1]);
					if (!(data->controllers[controllerIndex]->Handle(
							message + pos + 2, message[pos + 1])))
						return;
					handled = true;
					break;
				}
			}
			if (!handled) {
				Serial.println("Can't handle configuration.");
				return;
			}
			pos += 2 + message[pos + 1];
			if (pos >= length) {
				break;
			}
		}
	} else {
		Serial.print("Ignoring::Type is ");
		Serial.println((int) header->MessageType);
	}
}

SensorNodeSollicitState::~SensorNodeSollicitState() {
}

}
