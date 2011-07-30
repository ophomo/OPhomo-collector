/*
 * SerialHandlerIdleState.h
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#ifndef SERIALHANDLERIDLESTATE_H_
#define SERIALHANDLERIDLESTATE_H_

#include "SerialHandlerState.h"

namespace OPhomo {

class SerialHandlerIdleState: public OPhomo::SerialHandlerState {
public:
	SerialHandlerIdleState(SerialHandler* handler);

	void handle();

	virtual ~SerialHandlerIdleState();
};

}

#endif /* SERIALHANDLERIDLESTATE_H_ */
