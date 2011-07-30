/*
 * SerialHandlerState.cpp
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#include "SerialHandlerState.h"

namespace OPhomo {

SerialHandlerState::SerialHandlerState(SerialHandler* handler) : pos(handler->pos) {
	readBuffer = handler->readBuffer;
	serialHandler = handler;
}

SerialHandlerState::~SerialHandlerState() {
	// TODO Auto-generated destructor stub
}

}
