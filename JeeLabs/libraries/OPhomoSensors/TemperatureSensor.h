/*
 * TemperatureSensor.h
 *
 *  Created on: Jan 31, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef TEMPERATURESENSOR_H_
#define TEMPERATURESENSOR_H_
#include "stdint.h"
#include "TemperatureSensorMeasurement.h"

namespace OPhomo {
class TemperatureSensor {
public:
	TemperatureSensor() {};

	/**
	 * The most important function of a temperature sensor: reading the temperature.
	 * We use kelvin as bases. Unit is 1/64 of 1 degree Kelvin.
	 */
	virtual TemperatureSensorMeasurement ReadTemperature() = 0;

	virtual ~TemperatureSensor() {};

protected:
};
}

#endif /* TEMPERATURESENSOR_H_ */
