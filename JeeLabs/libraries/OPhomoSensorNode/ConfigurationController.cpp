/*
 * ConfigurationController.cpp
 *
 *  Created on: Feb 28, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */

#include "ConfigurationController.h"


namespace OPhomo {

ConfigurationController::ConfigurationController(SensorNode& sensorNode) {
	this->sensorNode = &sensorNode;
}

ConfigurationController::~ConfigurationController() {
}

byte ConfigurationController::DecodeInt(byte* message, byte maxLength,
		int& value) {
	// Check the length first.
	if (message[0] > maxLength) {
		value = 0;
		return 0;
	} else {
		Serial.print("L");
		Serial.println((int)message[0]);
		value = 0;
		byte pos = 0;
		while (pos < message[0]) {
//			Serial.print("\t");
//			Serial.println((int) message[1 + pos] );
			value += (((int) message[1 + pos]) << (pos * 8));
			pos++;
		}
		return pos + 1;
	}
}

}
