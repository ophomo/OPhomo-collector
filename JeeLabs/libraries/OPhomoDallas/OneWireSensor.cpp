/*
 * OneWireSensor.cpp
 *
 *  Created on: Feb 6, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "OneWireSensor.h"

namespace OPhomo {

OneWireSensor::OneWireSensor(OneWireSensorPin* inPin, DeviceAddress& inDeviceAddress) : pin(inPin) {
	memcpy(this->deviceAddress, &inDeviceAddress, 8);
}

void OneWireSensor::Select() {
	int i;

	pin->Write(0x55); // Choose ROM

	for (i = 0; i < 8; i++)
		pin->Write(deviceAddress[i]);
}



OneWireSensor::~OneWireSensor() {
}


}
