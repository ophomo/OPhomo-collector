/*
 * DallasPlug.cpp
 *
 *  Created on: Feb 1, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "DallasPlug.h"

namespace OPhomo {

DallasPlug::DallasPlug(JeePort* port) :
	Plug(port) {
	digitalController = NULL;
	analogController = NULL;
	parasite = false;
}

void DallasPlug::EnableDigitalPin() {
	if (digitalController == NULL) {
		digitalController = new OneWirePinController(&(port->getDigitalPin()));
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
		analogController = new OneWirePinController(&(port->getAnalogPin()));
	}
}

void DallasPlug::DisableAnalogPin() {
	if (analogController != NULL) {
		delete analogController;
		analogController = NULL;
	}
}

uint8_t DallasPlug::Search() {
	this->ClearSensors();
	// Try the digital pin first
	if (digitalController) {
		digitalController->Search(this);
	}
	if (analogController) {
		analogController->Search(this);
	}
	//	// Parasite or not ?
	//	if (analogController) {
	//		analogController->ResetSearch();
	//		while (analogController->Search(deviceAddress) && foundDevices
	//				< MAXDALLASSENSORS) {
	//			if (OneWirePinController::ValidAddress(deviceAddress)) {
	//				DallasTemperatureSensor& newSensor = sensors[foundDevices];
	//				newSensor.Initialize(analogController, deviceAddress);
	//				if (!parasite && newSensor.ReadPowerSupply())
	//					parasite = true;
	//
	//				uint8_t newConversionDelay = newSensor.GetConversionDelay();
	//				if (newConversionDelay > conversionDelay) {
	//					conversionDelay = newConversionDelay;
	//				}
	//				foundDevices++;
	//			}
	//		}
	//	}
	return position;
}

void DallasPlug::RequestTemperatures() {
	if (digitalController) {
		digitalController->Reset();
		digitalController->Skip();
		digitalController->Write(STARTCONVO, false /*parasite*/);
	}
	if (analogController) {
		analogController->Reset();
		analogController->Skip();
		analogController->Write(STARTCONVO, parasite);
	}
}

DallasPlug::~DallasPlug() {
	// TODO Auto-generated destructor stub
}

}
