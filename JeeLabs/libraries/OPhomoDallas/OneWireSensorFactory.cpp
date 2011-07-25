/*
 * OneWireSensorFactory.cpp
 *
 *  Created on: Feb 6, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "OneWireSensorFactory.h"
#include "DallasTemperatureSensor.h"
#include "HardwareSerial.h"
namespace OPhomo {

OneWireSensorFactory::OneWireSensorFactory() {
	for (position = 0; position < MAXDALLASSENSORS; position++) {
		sensors[position] = NULL;
	}
	position = 0;
}

uint8_t OneWireSensorFactory::Create(OneWirePinController* pinController,
		DeviceAddress& address) {
	switch ((int) address[0]) {
	case DS18S20MODEL:
	case DS18B20MODEL:
	case DS1822MODEL:
		sensors[position] = new DallasTemperatureSensor();
		sensors[position++]->Initialize(pinController, address);
		return 1;
	}
	return 0;
}

void OneWireSensorFactory::ClearSensors() {
	for (position = 0; position < MAXDALLASSENSORS; position++) {
		if (sensors[position] == NULL) {
			delete sensors[position];
			sensors[position] = NULL;
		}
	}
	position = 0;
}

uint8_t OneWireSensorFactory::GetMaxConversionDelay() {
	uint8_t maxConversionDelay = 0;
	uint8_t newConversionDelay;
	for ( uint8_t i = 0; i < position; i++ ) {

		if ( sensors[i] )  {
			newConversionDelay = sensors[i]->GetConversionDelay();
			if ( newConversionDelay  > maxConversionDelay )
				maxConversionDelay = newConversionDelay;
		}
	}
	return maxConversionDelay;
}

OneWireSensorFactory::~OneWireSensorFactory() {
	ClearSensors();
}

}
