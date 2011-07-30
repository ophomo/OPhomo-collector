/*
 * SensorNodeConfigAcceptState.h
 *
 *  Created on: 27 Jul 2011
 *      Author: admin@ophomo.org
 */

#ifndef SENSORNODECONFIGACCEPTSTATE_H_
#define SENSORNODECONFIGACCEPTSTATE_H_

#include "SensorNodeState.h"

namespace OPhomo {

class SensorNodeConfigAcceptState: public OPhomo::SensorNodeState {
public:
	SensorNodeConfigAcceptState(SensorNode* inNode);

	void handleMessage(byte* message, byte length);

	void tick();

	virtual ~SensorNodeConfigAcceptState();

	void sendAccept();
};

}

#endif /* SENSORNODECONFIGACCEPTSTATE_H_ */
