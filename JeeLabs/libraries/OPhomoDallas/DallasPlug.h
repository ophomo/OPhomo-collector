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
#include "OneWireSensorFactory.h"
#include "DallasTemperatureSensor.h"
// This defines the maximum number of sensors we support per port. This is low by default, but if you want, just increase it...
#define MAXDALLASSENSORS 8

namespace OPhomo {

class DallasPlug: public OPhomo::Plug, public OneWireSensorFactory {
public:
	DallasPlug(JeePort* port);

	void EnableDigitalPin();

	void DisableDigitalPin();

	void EnableAnalogPin();

	void DisableAnalogPin();

	uint8_t Search();

	inline uint8_t GetDeviceCount() {
		return position;
	}

	OneWireSensor** GetSensors() {
		return sensors;
	}

	void RequestTemperatures();

	virtual ~DallasPlug();
protected:
	OneWirePinController* digitalController;
	OneWirePinController* analogController;

	bool parasite;

	uint8_t conversionDelay;
};

}

#endif /* DALLASPLUG_H_ */
