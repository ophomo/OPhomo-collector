/*
 * SensorNodeState.h
 *
 *  Created on: 27 Jul 2011
 *      Author: decock
 */

#ifndef SENSORNODESTATE_H_
#define SENSORNODESTATE_H_
#include "Arduino.h"
#include "OPhomoProtocolHeader.h"
#include "MilliTimer.h"
#include "RF12Concatenator.h"


namespace OPhomo {
class SensorNode;
class ConfigurationController;


#define RF12_HDR_SIZE 3
#define MAX_CONTROLLERS 5


struct SensorNodeData {
	ProtocolStatus status;
	// The message we use to send the data.
	byte message[RF12_MAXDATA];

	// Timer used to see if when we need to send a message.
	MilliTimer timer;

	ConfigurationController** controllers;
	byte controllersSize;

	byte collectorNodeId;
};



class SensorNodeState {
public:
	SensorNodeState(SensorNode* inNode );

	virtual void handleMessage(byte* inMessage, byte length) = 0;

	virtual void tick() = 0;

	virtual ~SensorNodeState();

	RF12Module* getRF12Module();

protected:
	SensorNode* node;
	SensorNodeData* data;
};

}

#endif /* SENSORNODESTATE_H_ */
