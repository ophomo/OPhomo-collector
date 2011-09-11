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

void ConsoleMeasurementHandler::Handle(OPhomo::SensorMeasurement& measurement) {
	char result[10];
	result[measurement.toString(result,10)] = '\0';
	Serial.println(result);
}


ConsoleMeasurementHandler::~ConsoleMeasurementHandler() {
}

}
