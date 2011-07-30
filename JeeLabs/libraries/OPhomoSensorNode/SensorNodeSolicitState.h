/*
 * SensorNodeSolicitState.h
 *
 *  Created on: 27 Jul 2011
 *      Author: decock
 */

#ifndef SENSORNODESOLLICITSTATE_H_
#define SENSORNODESOLLICITSTATE_H_

#include "SensorNodeState.h"

namespace OPhomo {

class SensorNodeSolicitState: public OPhomo::SensorNodeState {
public:
	SensorNodeSolicitState(SensorNode* inNode);

	void handleMessage(byte* message, byte length);

	void tick();

	virtual ~SensorNodeSolicitState();
protected:
	/**
	 * This will send a solicit for a configuration message.
	 */
	void SolicitConfig();

};

}

#endif /* SENSORNODESOLLICITSTATE_H_ */
