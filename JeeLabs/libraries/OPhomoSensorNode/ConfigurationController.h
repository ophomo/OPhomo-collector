/*
 * ConfigurationController.h
 *
 *  Created on: Feb 28, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#ifndef CONFIGURATIONCONTROLLER_H_
#define CONFIGURATIONCONTROLLER_H_

#include "SensorNode.h"

namespace OPhomo {

class ConfigurationController {
public:
	ConfigurationController(SensorNode& node);

	/** This will handle an incoming message, and will apply the config on the node.
	 * If success, the number of bytes processed will be returned.
	 * If failed, 0 is returned.
	 */
	virtual byte HandleConfig(byte* message, byte length) = 0;

	/**
	 * This will reply to the configuration with details about e.g. sensors, ...
	 * It will return the number of bytes stored in the message.
	 */
	virtual byte ConfigReply() = 0;

	/**
	 * This will perform wathever the controlled object must do...
	 * Sensors will measure, others do nothing...
	 */
	virtual byte Perform() = 0;

	// This returns the type of the Controller.
	virtual byte getType() = 0;

	virtual ~ConfigurationController();

protected:
	SensorNode* sensorNode;

	static byte DecodeInt(byte* message, byte maxLength, int& value);


};

}

#endif /* CONFIGURATIONCONTROLLER_H_ */
