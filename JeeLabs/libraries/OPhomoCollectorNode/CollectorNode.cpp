/*
 * CollectorNode.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "SerialLogger.h"
#include "CollectorNode.h"
#include "OPhomoProtocolHeader.h"
#include "HardwareSerial.h"
#include "SerialConfigEncoder.h"
#include "log.h"

namespace OPhomo {

// This function must be implemented to handle config solicitations.
extern void handleConfigSolicit(byte node);
extern void handleConfigAccept(byte node, byte*, byte);
extern void handleConfigReject(byte node, byte*, byte);
extern void handleReport(byte node, byte*, byte);
extern void handleInternalMessage( byte*, byte);


CollectorNode::CollectorNode() {
	SerialConfigEncoder::transmitter.SetRF12Module(&rf12);
}

// This mimics the 'setup' method of the arduino program.
void CollectorNode::setup() {
	// -- I don't do anything here. Or should I ?
	rf12.init();
	rf12.setNodeId(RF12Concatenator::OPhomoListerNodeId);
	rf12.SaveConfig();
}

// This mimics the 'loop' method of the arduino program.
void CollectorNode::loop() {
	// Receive data...
	byte* messagePtr;
	byte len = rf12.TryReceive(messagePtr);
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) (messagePtr
			+ RF12_HDR_SIZE);
	if (len) {
		switch (header->MessageType) {
		case CONFIG_SOLICIT_TYPE: {
			handleConfigSolicit(header->SourceNode /*& 0x1F */);
		}
			break;
		case CONFIG_ACCEPT_TYPE: {
			handleConfigAccept(header->SourceNode /*& 0x1F */,
					messagePtr + RF12_HDR_SIZE + sizeof(OPhomoProtocolHeader),
					len - sizeof(OPhomoProtocolHeader));
		}
			break;
		case CONFIG_REJECT_TYPE: {
			handleConfigReject(header->SourceNode /*& 0x1F */,
					messagePtr + RF12_HDR_SIZE + sizeof(OPhomoProtocolHeader),
					len - sizeof(OPhomoProtocolHeader));
		}
			break;
		case REPORT_TYPE: {
			handleReport(header->SourceNode /*& 0x1F */,
					messagePtr + RF12_HDR_SIZE + sizeof(OPhomoProtocolHeader),
					len - sizeof(OPhomoProtocolHeader));

		}
			break;
		default: {
			//
			WARNING("UNKNOWN TYPE ");
			WARNINGLN((int) header->MessageType);
		}

		}
	}
}

void CollectorNode::SendConfigAdvertise(byte destination, byte* config,
		byte length) {
	// A dirty hack to save memory...
	byte dest = destination;
	byte* outMessage = config - 1;
    activityLed.On();
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) outMessage;
	header->MessageType = CONFIG_ADVERTISE_TYPE;
	header->SourceNode = rf12.getNodeId();
	// Send
	rf12.Send(dest, outMessage, length + 1, 0 /*false*/);
	outMessage[0] = dest;
	activityLed.Off();
}

CollectorNode::~CollectorNode() {
}

}
