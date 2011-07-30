/*
 * SerialHandlerState.h
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#ifndef SERIALHANDLERSTATE_H_
#define SERIALHANDLERSTATE_H_

#define SERIAL_BUFFER_SIZE 128

#define ASSERT_MIN_LENGTH(length) if ( data->pos <= length) { \
	ERROR("Assertion failed: length is smaller then "); \
	Serial.println(length); \
	return; \
}

#include "HardwareSerial.h"
#include "wiring.h"
#include "SerialConfigEncoder.h"


namespace OPhomo {

struct ConfigEncoderMapping {
	const byte* type; // Must be 4 bytes.
	SerialConfigEncoder *encoder;
};

struct SerialHandlerData {

	byte readBuffer[SERIAL_BUFFER_SIZE];
	byte pos;

	/**
	 * This is the mapping of installed SerialConfigEncoders and there config strings.
	 */
	ConfigEncoderMapping* encoders;
	byte encoderSize;

//		byte status;
//		byte destinationNode;
};


class SerialHandler;

class SerialHandlerState {
public:
	SerialHandlerState(SerialHandler* handler);

	virtual void handle() = 0;

	virtual ~SerialHandlerState();

protected:
	SerialHandler* serialHandler;
	SerialHandlerData* data;

};

}

#endif /* SERIALHANDLERSTATE_H_ */
