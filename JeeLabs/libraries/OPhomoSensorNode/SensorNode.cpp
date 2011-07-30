/*
 * SensorNode.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */


#include "SensorNode.h"
#include "HardwareSerial.h"
#include "ConfigurationController.h"
#include "SensorNodeSollicitState.h"

namespace OPhomo {

SensorNode::SensorNode() :
	JeeNode(), rf12Transmitter(&rf12) {
	data.status = CONFIG_SOLICIT;
	data.controllers = new ConfigurationController*[MAX_CONTROLLERS];
	data.controllersSize = 0;
}

void SensorNode::setup() {
	// Currently, I don't do anyting here. But this may change in the future.
	// E.g. In the setup, we could start requesting. But I don't think
	// this is a good idea.
	stateHandler = new SensorNodeSollicitState(this);
	rf12.init();
	data.timer.set(0);
}

void SensorNode::loop() {
	byte* inMessage;
	// It is best to try a receive in the loop, althoug we might only be able to send a request.
	// This due to internal RF12 things.
	byte len = rf12.TryReceive(inMessage);
	if (len) {
		Serial.println("SensorNode::Received a message.");
		stateHandler->handleMessage(inMessage, len);
		OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) (inMessage
				+ RF12_HDR_SIZE);
		switch (data.status) {
		case CONFIG_SOLICIT: {
			// This is probably a config message ?
			if (header->MessageType == CONFIG_ADVERTISE_TYPE) {
				if (this->ApplyConfig(
						inMessage + RF12_HDR_SIZE
								+ sizeof(OPhomoProtocolHeader),
						len - sizeof(OPhomoProtocolHeader))) {
					if (data.status == CONFIG_ACCEPT) {
						// We need to send a config accept
						data.collectorNodeId = header->SourceNode;
						data.status = OPERATIONAL;
					}
				} else {
					// We need to send a config reject.
				}
			} else {
				Serial.print("Type is ");
				Serial.println((int) header->MessageType);
			}

		}
			break;
		}
	}
	data.timer.poll();
	switch (data.status) {
	case CONFIG_SOLICIT: {
		if (data.timer.idle()) {
			SolicitConfig();
			data.timer.set(5000);
		}
	}
		break;
	}
}

void SensorNode::SolicitConfig() {
	// Configure the message.
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) data.message;
	header->MessageType = CONFIG_SOLICIT_TYPE;
	header->SourceNode = rf12.getNodeId();
	// Send
	rf12.Send((byte) 0, data.message, (uint8_t) CONFIG_SOLICIT_LENGTH, 0 /*false*/);
}

bool SensorNode::ApplyConfig(byte* message, byte len) {
	Serial.print("Config received with length ");
	Serial.println((int) len);
	byte pos = 0;
	while (1) {
		// ASSERT LENGTH
		Serial.print("Checking message type : ");
		Serial.print((int) message[pos]);
		Serial.print(" with length ");
		Serial.println((int) message[pos + 1]);
		bool handled = false;
		if (message[pos] == 0 && message[pos + 1] == 0) {
			// We reached the end of the configuration.
			data.status = CONFIG_ACCEPT;
			return true;
		}
		for (byte controllerIndex = 0; controllerIndex < data.controllersSize; controllerIndex++) {
			if (message[pos] == data.controllers[controllerIndex]->getType()) {
				Serial.print("Found controller, handling message with size ");
				Serial.println((int) message[pos + 1]);
				if (!(data.controllers[controllerIndex]->Handle(message + pos + 2,
						message[pos + 1])))
					return false;
				handled = true;
				break;
			}
		}
		if (!handled) {
			Serial.println("Can't handle configuration.");
			return false;
		}
		pos += 2 + message[pos + 1];
		if (pos >= len) {
			break;
		}
	}
	return true;
}

void SensorNode::Register(ConfigurationController* controller) {
	Serial.print("Registering controller at position ");
	Serial.print((int) data.controllersSize);
	Serial.println(".");
	if (data.controllersSize < MAX_CONTROLLERS) {
		data.controllers[data.controllersSize++] = controller;
	}

}

void SensorNode::SendConfigAccept(byte* message, byte len) {
	byte dest = data.collectorNodeId;
	byte* outMessage = message - 1;

	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) outMessage;
	header->MessageType = CONFIG_ACCEPT_TYPE;
	header->SourceNode = rf12.getNodeId();
	// Send
	rf12.Send( dest, outMessage, len + 1, 1);
	outMessage[0] = dest;
}

SensorNode::~SensorNode() {
	if ( stateHandler )
		delete stateHandler;
}

void SensorNode::setStateHandler(SensorNodeState* newHandler){
	SensorNodeState* temp = stateHandler;
	stateHandler = newHandler;
	if ( temp != NULL )
		delete temp;
};

}
