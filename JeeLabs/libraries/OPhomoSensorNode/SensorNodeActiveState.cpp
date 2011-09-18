/*
 * SensorNodeActiveState.cpp
 *
 *  Created on: 3 Aug 2011
 *      Author: OPhomo
 */

#include "SensorNodeActiveState.h"
#include "ConfigurationController.h"
#include "log.h"

namespace OPhomo {

SensorNodeActiveState::SensorNodeActiveState(SensorNode* inNode) :
	SensorNodeState(inNode) {
	INFOLN("<ACTIVE>");
}

void SensorNodeActiveState::handleMessage(byte* message, byte length) {
	OPhomoProtocolHeader* header = (OPhomoProtocolHeader*) (message
			+ RF12_HDR_SIZE);
	byte pos = RF12_HDR_SIZE + sizeof(OPhomoProtocolHeader);
	bool handled;
	// What do we accept...
}

void SensorNodeActiveState::tick() {
	if (data->timer.idle()) {
		//		sendMeasurement();
		data->timer.set(5000);
		// -- Perform the actions on the controllers.
		node->rf12Transmitter.SetMessageType(REPORT_TYPE);
		for (byte controllerIndex = 0; controllerIndex < data->controllersSize; controllerIndex++) {
			data->controllers[controllerIndex]->Perform();
		}
		node->rf12Transmitter.LastPartSend();

	}

}

SensorNodeActiveState::~SensorNodeActiveState() {
	// TODO Auto-generated destructor stub
}

}
