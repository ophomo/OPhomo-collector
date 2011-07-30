/*
 * RF12Controller.cpp
 *
 *  Created on: Feb 28, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "RF12Controller.h"

namespace OPhomo {

RF12Controller::RF12Controller(SensorNode& sensorNode) :
	ConfigurationController(sensorNode) {
	sensorNode.Register(this);
}

byte RF12Controller::ConfigReply() {
	return 0;
}


byte RF12Controller::Handle(byte* message, byte length) {
	byte pos;
	for ( pos = 0; pos < length; pos++) {
		Serial.print("P");
		Serial.println((int)pos);
		switch (message[pos]) {
		case 0x01: {
			// NodeID
			int nodeId = 0;
			byte decodedLength = ConfigurationController::DecodeInt(message
					+ pos + 1, length - pos - 2, nodeId);
			if (decodedLength == 0) {
				ERRORLN()("RF12::NodeID");
				return 0;
			} else {
				sensorNode->getRF12().setNodeId((byte) nodeId);
				pos += decodedLength;
			}
		}
			break;
		case 0x02: {
			// GroupID
			int groupId = 0;
			byte decodedLength = ConfigurationController::DecodeInt(message
					+ pos + 1, length - pos - 2, groupId);
			if (decodedLength == 0) {
				ERRORLN("RF12::GroupID");
				return 0;
			} else {
				sensorNode->getRF12().setGroupId((byte) groupId);
				pos += decodedLength;
			}
		}
			break;
		case 0x03: {
			// Band
			int band = 0;
			byte decodedLength = ConfigurationController::DecodeInt(message
					+ pos + 1, length - pos - 2, band);
			if (decodedLength == 0) {
				ERRORLN("RF12::Band");
				return 0;
			} else {
				sensorNode->getRF12().setBand((byte) band);
				pos += decodedLength;
			}
		}
			break;
		case 0x04: {
			// Save config
			int save = 0;
			byte decodedLength = ConfigurationController::DecodeInt(message
					+ pos + 1, length - pos - 2, save);
			if (decodedLength == 0) {
				ERRORLN("RF12::Decode::Save");
				return 0;
			} else {
				if (save > 0) {
					if (!sensorNode->getRF12().SaveConfig()) {
						ERRORLN("RF12::Save");
						return 0;
					}
				}
				pos += decodedLength;
			}
		}
			break;
		default: {
			Serial.print("RF12::Unknown item:");
			Serial.println((int) message[pos]);
		}
		}
	}
	return pos;
}

RF12Controller::~RF12Controller() {
	// TODO Auto-generated destructor stub
}

}
