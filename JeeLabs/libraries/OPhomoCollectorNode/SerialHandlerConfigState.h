/*
 * SerialHandlerConfigState.h
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#ifndef SERIALHANDLERCONFIGSTATE_H_
#define SERIALHANDLERCONFIGSTATE_H_

#include "SerialHandlerState.h"


namespace OPhomo {

class SerialHandlerConfigState: public OPhomo::SerialHandlerState {
public:
	virtual ~SerialHandlerConfigState();

	void handle();

	SerialHandlerConfigState(SerialHandler* handler);
};

}

#endif /* SERIALHANDLERCONFIGSTATE_H_ */
