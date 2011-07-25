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
#include <string.h>

namespace OPhomo {

class TemperatureSensorData {
public:
	TemperatureSensorData();

	inline void Set(uint16_t direct) {
		measurement = direct;
	}


	double GetCelsius() {
		return (((double(measurement)) * 1 / 64) - 273.15);
	}

	char* toStringCelsius() {
		char* result = new char[10];
		toStringCelsius(result);
		return result;
	}

	void toStringCelsius(char* result);

	virtual ~TemperatureSensorData();

	static char* DoubleToString(char* result, double value, uint8_t digits);
protected:
	uint16_t measurement;
};

}

#endif /* TEMPERATURESENSORDATA_H_ */
