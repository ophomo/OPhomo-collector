/*
 * SerialHandlerState.cpp
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#include "SerialHandlerState.h"
#include "SerialHandler.h"
namespace OPhomo {

SerialHandlerState::SerialHandlerState(SerialHandler* handler) {
	serialHandler = handler;
	data = &(handler->data);
}

SerialHandlerState::~SerialHandlerState() {
	// TODO Auto-generated destructor stub
}

}
