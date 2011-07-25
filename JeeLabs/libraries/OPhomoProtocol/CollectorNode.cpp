/*
 * CollectorNode.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */

#include "CollectorNode.h"
#include "OPhomoProtocolHeader.h"
#include "HardwareSerial.h"
#include "SerialConfigEncoder.h"
namespace OPhomo {

// This function must be implemented to handle config solicitations.
extern void handleConfigSolicit(byte node);

CollectorNode::CollectorNode() {
	SerialConfigEncoder::transmitter.SetRF12Module(&rf12);
}

// This mimics the 'setup' method of the arduino program.
void CollectorNode::setup() {
	// -- I don't do anything here. Or should I ?
	rf12.init();
}

// This mimics the 'loop' method of the arduino program.
void CollectorNode::loop() {
	// Receive data...
	byte* messagePtr;
	byte len = rf12.TryReceive(messagePtr);
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) (messagePtr + 3);
	if (len) {
		switch (header->MessageType) {
		case CONFIG_SOLICIT_TYPE: {
			handleConfigSolicit(header->SourceNode /*& 0x1F */);
		}
			break;
		}
	}
}

void CollectorNode::SendConfigAdvertise(byte destination, byte* config, byte length) {
	// A dirty hack to save memory...
	byte dest = destination;
	byte* outMessage = config - 1;

	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) outMessage;
	header->MessageType = CONFIG_ADVERTISE_TYPE;
	header->SourceNode = rf12.getNodeId();
	// Send
	rf12.Send( dest, outMessage, length + 1, 0 /*false*/);
	outMessage[0] = dest;
}

CollectorNode::~CollectorNode() {
}

}
