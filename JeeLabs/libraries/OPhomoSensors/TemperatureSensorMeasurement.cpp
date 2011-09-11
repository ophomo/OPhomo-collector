/*
 * TemperatureSensorData.cpp
 *
 *  Created on: Feb 1, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
*/

#include "TemperatureSensorMeasurement.h"
#include <stdio.h>
#include <stdlib.h>

namespace OPhomo {

#define commaNotation '.'

TemperatureSensorMeasurement::TemperatureSensorMeasurement() :
	SensorMeasurement() {
	// TODO Auto-generated constructor stub
	measurement = 0;

}


TemperatureSensorMeasurement::~TemperatureSensorMeasurement() {
	// TODO Auto-generated destructor stub
}

#ifdef SENSORTOSTRING
uint8_t TemperatureSensorMeasurement::toStringCelsius(char* result) {
	return DoubleToString(result, GetCelsius(), 3);
}

uint8_t TemperatureSensorMeasurement::toString(char* result, uint8_t inSize) {
	return DoubleToString(result, GetCelsius(), 3, inSize);
}

byte TemperatureSensorMeasurement::DoubleToString(char* result, double value,
		uint8_t digits, uint8_t resultSize) {
	// Handle negative numbers
	uint8_t pos = 0;
	if (value < 0.0 ) {
		result[pos++] = '-';
		value = -value;
		if (!(--resultSize)) {
			return pos;
		}
	}


	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i = 0; i < digits; ++i)
		rounding /= 10.0;

	value += rounding;

	// Extract the integer part of the number and print it
	int int_part = (int) value;
	double remainder = value - (double) int_part;
	itoa(int_part, result + pos, 10);
    while ( int_part > 0 ) {
    	int_part = int_part / 10;
        pos++;
		if (!(--resultSize)) {
			return pos;
		}
    }

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0)
		result[pos++] = commaNotation;

	// Extract digits from the remainder one at a time
	while (digits-- > 0) {
		remainder *= 10.0;
		int toPrint = int(remainder);
        itoa(toPrint, result + pos, 10);
        pos++;
		remainder -= toPrint;
		if (!(--resultSize)) {
			return pos;
		}
	}
	return pos;
}
#endif

}
