/*
 * ConsoleMeasurementHandler.h
 *
 *  Created on: 11 Sep 2011
 *      Author: OPhomo
 */

#ifndef CONSOLEMEASUREMENTHANDLER_H_
#define CONSOLEMEASUREMENTHANDLER_H_

#include "MeasurementHandler.h"

namespace OPhomo {

class ConsoleMeasurementHandler: public OPhomo::MeasurementHandler {
public:
	ConsoleMeasurementHandler();

	void Handle(SensorMeasurement& measurement);

	virtual ~ConsoleMeasurementHandler();
};

}

#endif /* CONSOLEMEASUREMENTHANDLER_H_ */
