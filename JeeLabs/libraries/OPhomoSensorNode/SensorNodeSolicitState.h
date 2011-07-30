/*
 * SensorNodeSollicitState.h
 *
 *  Created on: 27 Jul 2011
 *      Author: decock
 */

#ifndef SENSORNODESOLLICITSTATE_H_
#define SENSORNODESOLLICITSTATE_H_

#include "SensorNodeState.h"

namespace OPhomo {

class SensorNodeSollicitState: public OPhomo::SensorNodeState {
public:
	SensorNodeSollicitState(SensorNode* inNode);

	void handleMessage(byte* message, byte length);

	virtual ~SensorNodeSollicitState();
};

}

#endif /* SENSORNODESOLLICITSTATE_H_ */
