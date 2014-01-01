/*
 * DallasPlug.h
 *
 *  Created on: Feb 1, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef DALLASPLUG_H_
#define DALLASPLUG_H_

#include "Plug.h"
#include "OneWirePinController.h"

namespace OPhomo {

class DallasPlug: public OPhomo::Plug {
public:
	DallasPlug(JeePort* port);

	void EnableDigitalPin();

	void DisableDigitalPin();

	void EnableAnalogPin();

	void DisableAnalogPin();

	uint8_t Search();

	OneWireSensor* analogSensor(uint8_t i) {
		if (analogController)
			return (*analogController)[i];
		else
			return NULL;
	}
	OneWireSensor* digitalSensor(uint8_t i) {
		if (digitalController)
			return (*digitalController)[i];
		else
			return NULL;

	}

//	void RequestTemperatures(MeasurementHandler* handler);

	uint16_t InitRead(byte pos);

	uint16_t ReadAnalogSensor(MeasurementHandler* handler) {
		return analogController ? analogController->SensorRead(handler) : 0;
	}

	uint16_t ReadDigitalSensor(MeasurementHandler* handler) {
		return digitalController ? digitalController->SensorRead(handler) : 0;
	}

	uint16_t InitReadAll();


	uint16_t ReadAllAnalogSensors(MeasurementHandler* handler) {
		return analogController ? analogController->SensorReadAll(handler) : 0;
	}

	uint16_t ReadAllDigitalSensors(MeasurementHandler* handler) {
		return digitalController ? digitalController->SensorReadAll(handler) : 0;
	}


	virtual ~DallasPlug();
protected:
	OneWirePinController* digitalController;
	OneWirePinController* analogController;

	bool parasite;

	uint8_t conversionDelay;
};

}

#endif /* DALLASPLUG_H_ */
