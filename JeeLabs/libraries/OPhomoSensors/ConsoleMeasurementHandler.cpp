/*
 * ConsoleMeasurementHandler.cpp
 *
 *  Created on: 11 Sep 2011
 *      Author: OPhomo
 */

#include "ConsoleMeasurementHandler.h"
#include "HardwareSerial.h"

namespace OPhomo {

ConsoleMeasurementHandler::ConsoleMeasurementHandler() {
}

uint8_t ConsoleMeasurementHandler::Handle(OPhomo::SensorMeasurement& measurement) {
	char result[10];
	result[measurement.toString(result,10)] = '\0';
	Serial.println(result);
	// This is not a nice way, but good enough at the moment.
	return 10;
}


ConsoleMeasurementHandler::~ConsoleMeasurementHandler() {
}

}
