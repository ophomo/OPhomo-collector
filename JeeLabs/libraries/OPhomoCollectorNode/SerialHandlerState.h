/*
 * SerialHandlerState.h
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#ifndef SERIALHANDLERSTATE_H_
#define SERIALHANDLERSTATE_H_

#define SERIAL_BUFFER_SIZE 128

namespace OPhomo {

class SerialHandler;

class SerialHandlerState {
public:
	SerialHandlerState(SerialHandler* handler);

	virtual void handle() = 0;

	virtual ~SerialHandlerState();

protected:
	SerialHandler* serialHandler;
	byte* readBuffer;
	byte& pos;
};

}

#endif /* SERIALHANDLERSTATE_H_ */
