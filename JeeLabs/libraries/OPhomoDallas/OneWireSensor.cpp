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

OneWireSensor::OneWireSensor(OneWireSensorChainInterface* inWrappee , DeviceAddress& inDeviceAddress) {
	wrappee = inWrappee;
	memcpy(this->deviceAddress, &inDeviceAddress, 8);
}

void OneWireSensor::Select() {
	int i;

	wrappee->Write(0x55); // Choose ROM

	for (i = 0; i < 8; i++)
		wrappee->Write(deviceAddress[i]);
}

uint8_t OneWireSensor::InitReadSensor() {
	uint8_t otherDelay = wrappee->InitReadSensor();
	uint8_t myDelay = GetConversionDelay();
	return myDelay > otherDelay ? myDelay  : otherDelay;
}


OneWireSensor::~OneWireSensor() {
	delete wrappee;

}

OneWireSensor* OneWireSensor::operator[] (uint8_t i) {
	if ( i == 0 ) {
		return this;
	} else {
		return (*wrappee)[--i];

};
}

}
