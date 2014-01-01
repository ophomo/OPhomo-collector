/*
 * RF12Controller.h
 *
 *  Created on: Feb 28, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef RF12CONTROLLER_H_
#define RF12CONTROLLER_H_

#include "OPhomoProtocolHeader.h"
#include "ConfigurationController.h"

namespace OPhomo {

class RF12Controller: public ConfigurationController {
public:
	RF12Controller(SensorNode& sensorNode);

	byte HandleConfig(byte* message, byte length);

	byte ConfigReply();

	byte Perform() {
		// We can reply with our statistics of the RF12 module.
		return 0;
	}

	virtual ~RF12Controller();

	byte getType() {
		return type;
	}

protected:
	static const byte type = RF12_CONFIG_TYPE;
};

}

#endif /* RF12CONTROLLER_H_ */
