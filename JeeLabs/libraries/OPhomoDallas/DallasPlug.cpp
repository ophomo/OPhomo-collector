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

void DallasPlug::RequestTemperatures(MeasurementHandler* handler) {
	uint8_t wait = 0;
	if (digitalController) {
		wait = digitalController->InitSensorRead();
	}
	if (analogController) {
		uint8_t analogResult = analogController->InitSensorRead();
		wait = wait > analogResult ? wait : analogResult;
	}
	delay(wait);
	if (digitalController) {
		digitalController->Read(handler);
	}
	if (analogController) {
		analogController->Read(handler);
	}
}

DallasPlug::~DallasPlug() {
}

}
