/*
 * SensorMeasurement.h
 *
 *  Created on: 11 Sep 2011
 *      Author: OPhomo
 *
 *  Interface for a measurement done by a sensor node.
 *  This allows us to create different measurements but use the same way to transport them to the collector node.
 */

#ifndef SENSORMEASUREMENT_H_
#define SENSORMEASUREMENT_H_

#define SENSORTOSTRING 1

#include <stdint.h>
#include <string.h>

namespace OPhomo {



class SensorMeasurement {
public:
	SensorMeasurement();

	/**
	 * Each Sensor meauserement has its unique type, defined in SensorMeasurementTypes.h
	 */
	virtual uint8_t getType() = 0;

	/**
	 * Returns the size of an object. Can be used to transmit an object from a SensorNode to a CollectorNode.
	 */
	virtual uint8_t getSize() = 0;

#ifdef SENSORTOSTRING
	/**
	 * This is a textual representation of a measurement.
	 */
	virtual uint8_t toString(char* text, uint8_t inSize) = 0;
#endif

	virtual void toBytes(uint8_t* store) = 0;

	virtual ~SensorMeasurement();
};

}

#endif /* SENSORMEASUREMENT_H_ */
