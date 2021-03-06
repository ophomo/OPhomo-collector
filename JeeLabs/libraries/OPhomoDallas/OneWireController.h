/*
 * OneWireController.h
 *
 *  Created on: Mar 13, 2011
 *      Author: decock
 */

#ifndef ONEWIRECONTROLLER_H_
#define ONEWIRECONTROLLER_H_

#include "ConfigurationController.h"
#include "DallasPlug.h"
#define MAX_DALLAS_PLUGS 4

namespace OPhomo {

class OneWireController: public OPhomo::ConfigurationController {
public:
	OneWireController(SensorNode& node);

	virtual byte HandleConfig(byte* message, byte length);

	byte Perform();

	static byte getSType() {
		return type;
	}

	byte getType() {
		return type;
	}

	byte ConfigReply();

	virtual ~OneWireController();

	DallasPlug* dallasPlugs[MAX_DALLAS_PLUGS];

protected:
	static const byte type = ONEWIRE_SENSOR_CONFIG_TYPE;

};

}

#endif /* ONEWIRECONTROLLER_H_ */
