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
#include "SensorNodeSolicitState.h"

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

	rf12.init();
	Serial.print("NodeID:");
	Serial.println((int)rf12.getNodeId());
	Serial.print("Band:");
	Serial.println((int)rf12.getBand());
	data.timer.set(0);
	stateHandler = new SensorNodeSolicitState(this);
}

void SensorNode::loop() {
	byte* inMessage;
	// It is best to try a receive in the loop, althoug we might only be able to send a request.
	// This due to internal RF12 things.
	byte len = rf12.TryReceive(inMessage);
	if (len) {
//		Serial.println("SensorNode::Received a message.");
		stateHandler->handleMessage(inMessage, len + RF12_HDR_SIZE);
	}
	if ( data.timer.poll() )
		stateHandler->tick();
	// This check makes sure that the timer is always armed.
	if ( data.timer.idle() )
		data.timer.set(500);
}




void SensorNode::Register(ConfigurationController* controller) {
/*	Serial.print("Registering controller ");
	Serial.print((int) controller );
	Serial.print(" 	at position ");
	Serial.print((int) data.controllersSize);
	Serial.println(".");*/
	if (data.controllersSize < MAX_CONTROLLERS) {
		data.controllers[data.controllersSize++] = controller;
	}

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
