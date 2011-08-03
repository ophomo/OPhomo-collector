/*
 * SensorNodeActiveState.h
 *
 *  Created on: 3 Aug 2011
 *      Author: OPhomo
 */

#ifndef SENSORNODEACTIVESTATE_H_
#define SENSORNODEACTIVESTATE_H_

#include "SensorNodeState.h"

namespace OPhomo {

class SensorNodeActiveState: public OPhomo::SensorNodeState {
public:
	SensorNodeActiveState(SensorNode* inNode);

	void handleMessage(byte* message, byte length);

	void tick();

	virtual ~SensorNodeActiveState();
};

}

#endif /* SENSORNODEACTIVESTATE_H_ */
