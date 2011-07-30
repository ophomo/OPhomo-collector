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
#include "wiring.h"
#include "SerialConfigEncoder.h"

namespace OPhomo {

#define SERIAL_BUFFER_SIZE 128

class SerialHandler {
public:
	SerialHandler();

	// This will try to handle incoming message. If no \CR is received, we wait until we see one.
	void Try();

	void RegisterEncoder( const byte* type, SerialConfigEncoder* encoder);

	virtual ~SerialHandler();


protected:
	byte readBuffer[ SERIAL_BUFFER_SIZE ];
	byte pos;

	// This will handle a full command line.
	void Handle();

	// This is a mapping between a string and the encoder. E.g. RF12 will use the RF12SerialConfigEncoder.
	struct ConfigEncoderMapping {
		const byte* type; // Must be 4 bytes.
		SerialConfigEncoder *encoder;
	};

	/**
	 * This is the mapping of installed SerialConfigEncoders and there config strings.
	 */
	ConfigEncoderMapping* encoders;
	byte encoderSize;




	byte status;
	byte destinationNode;
};

}

#endif /* SERIALHANDLER_H_ */
