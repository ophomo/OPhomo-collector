/*
 * SerialHandler.h
 *
 *  Created on: Feb 21, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef SERIALHANDLER_H_
#define SERIALHANDLER_H_
#include "HardwareSerial.h"
#include "Arduino.h"
#include "SerialConfigEncoder.h"
#include "SerialHandlerState.h"

namespace OPhomo {

class CollectorNode;
class SerialHandler {
public:
	SerialHandler();

	// This will try to handle incoming message. If no \CR is received, we wait until we see one.
	void Try();

	void RegisterEncoder(const byte* type, SerialConfigEncoder* encoder);

	virtual ~SerialHandler();

	void setHandler(SerialHandlerState* newState);

protected:
	SerialHandlerState* state;

	SerialHandlerData data;

	friend class SerialHandlerState;
	friend class CollectorNode;

};

}

#endif /* SERIALHANDLER_H_ */
