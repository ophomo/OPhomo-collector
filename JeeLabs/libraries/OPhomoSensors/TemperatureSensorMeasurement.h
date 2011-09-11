/*
 * TemperatureSensorData.h
 *
 *  Created on: Feb 1, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef TEMPERATURESENSORDATA_H_
#define TEMPERATURESENSORDATA_H_
#include <stdint.h>
#include "SensorMeasurement.h"
#include "SensorMeasurementTypes.h"

#include <string.h>
#include "wiring.h"
namespace OPhomo {

class TemperatureSensorMeasurement : public SensorMeasurement {
public:
	TemperatureSensorMeasurement();

	inline void Set(uint16_t direct) {
		measurement = direct;
	}


	double GetCelsius() {
		return (((double(measurement)) * 1 / 64) - 273.15);
	}

	virtual ~TemperatureSensorMeasurement();

	static byte DoubleToString(char* result, double value, uint8_t digits, uint8_t resultSize = -1);

#ifdef SENSORTOSTRING
	char* toStringCelsius() {
		char* result = new char[10];
		toStringCelsius(result);
		return result;
	}

	uint8_t toStringCelsius(char* result);

    uint8_t toString(char*result, uint8_t inSize);

#endif

    uint8_t getSize() {
    	return sizeof(TemperatureSensorMeasurement);
    }

    uint8_t getType() {
    	return TemperatureSensorType;
    }

protected:
	uint16_t measurement;
};

}

#endif /* TEMPERATURESENSORDATA_H_ */
