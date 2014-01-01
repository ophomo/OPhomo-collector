/*
 * DallasPlug.cpp
 *
 *  Created on: Feb 1, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "DallasPlug.h"
#include "OneWireSensorPin.h"
namespace OPhomo {

DallasPlug::DallasPlug(JeePort* port) :
	Plug(port) {
	digitalController = NULL;
	analogController = NULL;
	parasite = false;
}

void DallasPlug::EnableDigitalPin() {
	if (digitalController == NULL) {
		digitalController = new OneWirePinController(
				new OneWireSensorPin(&(port->getDigitalPin())));
	}
}

void DallasPlug::DisableDigitalPin() {
	if (digitalController != NULL) {
		delete digitalController;
		digitalController = NULL;
	}
}

void DallasPlug::EnableAnalogPin() {
	if (analogController == NULL) {
		analogController = new OneWirePinController(
				new OneWireSensorPin(&(port->getAnalogPin())));
	}
}

void DallasPlug::DisableAnalogPin() {
	if (analogController != NULL) {
		delete analogController;
		analogController = NULL;
	}
}

uint8_t DallasPlug::Search() {
	// Try the digital pin first
	uint8_t result = 0;
	if (digitalController) {
		result += digitalController->Search();
	}
	if (analogController) {
		result += analogController->Search();
	}
	return result;
}

uint16_t DallasPlug::InitRead(byte pos) {
	// Check if there is a sensor at that position
	uint16_t time2WaitD, time2WaitA;
	time2WaitD = time2WaitA = 0;
	if ( digitalController ) {
		time2WaitD = digitalController->InitSensorRead(pos);
	};
	if ( analogController ) {
		time2WaitA = analogController->InitSensorRead(pos);
	};
	return (time2WaitA > time2WaitD ? time2WaitA : time2WaitD);
}

uint16_t DallasPlug::InitReadAll() {
	// Check if there is a sensor at that position
	uint16_t time2WaitD, time2WaitA;
	time2WaitD = time2WaitA = 0;
	if ( digitalController ) {
		time2WaitD = digitalController->InitSensorReadAll();
	};
	if ( analogController ) {
		time2WaitA = analogController->InitSensorReadAll();
	};
	return (time2WaitA > time2WaitD ? time2WaitA : time2WaitD);
}


/*
void DallasPlug::RequestTemperatures(MeasurementHandler* handler) {
	if (digitalController) {
		digitalController->Read(handler);
	}
	if (analogController) {
		analogController->Read(handler);
	}
}
*/

DallasPlug::~DallasPlug() {
}

}
