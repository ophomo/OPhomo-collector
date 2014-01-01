/*
 * MeasurementHandler.h
 *
 *  Created on: 11 Sep 2011
 *      Author: OPhomo
 *
 *  Interface for measurement handlers ( log, console, RF12, ... )
 */

#ifndef MEASUREMENTHANDLER_H_
#define MEASUREMENTHANDLER_H_


#include "SensorMeasurement.h"
namespace OPhomo {

class MeasurementHandler {
public:
	MeasurementHandler();

	// The method which will handle a measurement.
	virtual uint8_t Handle(SensorMeasurement& measurement) = 0;

	virtual ~MeasurementHandler();
};

}

#endif /* MEASUREMENTHANDLER_H_ */
