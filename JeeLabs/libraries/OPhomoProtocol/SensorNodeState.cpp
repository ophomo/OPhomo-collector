/*
 * SensorNodeState.cpp
 *
 *  Created on: 27 Jul 2011
 *      Author: decock
 */

#include "SensorNodeState.h"
#include "SensorNode.h"
namespace OPhomo {

SensorNodeState::SensorNodeState(SensorNode* inNode) {
	node = inNode;
	data = &(inNode->data);
}

SensorNodeState::~SensorNodeState() {
	// TODO Auto-generated destructor stub
}

}
