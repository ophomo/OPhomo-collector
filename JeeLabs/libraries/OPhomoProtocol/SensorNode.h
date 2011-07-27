/*
 * SensorNode.h
 *
 *  Created on: Feb 15, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef SENSORNODE_H_
#define SENSORNODE_H_

#include "JeeNode.h"
#include "OPhomoProtocolHeader.h"
#include "MilliTimer.h"
#include "RF12Concatenator.h"
#include "SensorNodeState.h"

namespace OPhomo {

class ConfigurationController;

class SensorNode: public JeeNode {
public:
	SensorNode();

	/**
	 *  This mimics the 'setup' method of the arduino program.
	 */
	void setup();

	/**
	 * This mimics the 'loop' method of the arduino program.
	 */
	void loop();

	/**
	 * Register controllers which can be used to configure this JeeNode.
	 * This method must not be called by the user. Controllers are doing this in their constructor.
	 */
	void Register(ConfigurationController* controller);

	/**
	 * This sends a config accept to the collector.
	 */
	void SendConfigAccept(byte* message, byte len);

	void ConfigReplyAppend(byte* reply, byte len);

	void ConfigReplyDone();

	virtual ~SensorNode();

	RF12Concatenator rf12Transmitter;

	void setStateHandler(SensorNodeState*);

protected:
	SensorNodeState* stateHandler;

	SensorNodeData data;

	friend class SensorNodeState;

	/**
	 * This will send a solicitation for a configuration message.
	 */
	void SolicitConfig();

	/**
	 * This will send a config accept with details about the config, like sensors, ...
	 */
	void AcceptConfig();

	bool ApplyConfig(byte* message, byte len);

};

}

#endif /* JEECOMPROTOCOL_H_ */
