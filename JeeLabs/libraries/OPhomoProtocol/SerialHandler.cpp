/*
 * SerialHandler.cpp
 *
 *  Created on: Feb 21, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "SerialHandler.h"
#include "OPhomoProtocolHeader.h"
#define SH_IDLE 0
#define SH_CONFIGURING 1

#define ASSERT_MIN_LENGTH(length) if ( pos <= length) { \
	ERROR("Assertion failed: length is smaller then "); \
	Serial.println(length); \
	return; \
}

namespace OPhomo {

SerialHandler::SerialHandler() {
	// TODO Auto-generated constructor stub
	pos = 0;
	status = SH_IDLE;
	// Currently, we support just 5.
	encoders = new ConfigEncoderMapping[5];
	encoderSize = 0;
}

void SerialHandler::Try() {
	if (Serial.available()) {
		readBuffer[pos] = Serial.read();
		if (readBuffer[pos] == (byte) 0x0D) {
			// Handle the command.
			this->Handle();
			pos = 0;
		} else {
			if ((unsigned char) pos < (SERIAL_BUFFER_SIZE - 1)) {
				pos++;
			} else {
				ERRORLN("BUFFER FULL");
				pos = 0;
			}
		}
	}
}

SerialHandler::~SerialHandler() {
	// TODO Auto-generated destructor stub
}

void SerialHandler::Handle() {
	/*	Serial.print("Handle this : \'");
	 for (byte i = 0; i < pos; i++)
	 Serial.print(readBuffer[i]);
	 Serial.println("\'");*/
	switch (status) {
	case SH_IDLE: {
		LOGLN("Checking in status idle.");
		// We must have one of our COMMANDS
		ASSERT_MIN_LENGTH (2)
		if (readBuffer[0] == 'C' && readBuffer[1] == 'A') {
			// Configuration request.
			// Parse the node id.
			destinationNode = 0;
			for (int i = 2; i < pos; i++) {
				if ('0' <= readBuffer[i] && readBuffer[i] <= '9')
					destinationNode = destinationNode * 10 + readBuffer[i]
							- '0';
				else
					return;
			}
			LOG("Configuring node ");
			Serial.println((int) destinationNode);
			SerialConfigEncoder::transmitter.SetDestinationNode(destinationNode);
			status = SH_CONFIGURING;
		} else {
			ERRORLN("UNKNOWN COMMAND!");
		}
	}
		break;
	case SH_CONFIGURING: {
		LOGLN("Checking in status configuring");
		// First trim spaces and tabs.
		byte start;
		for (start = 0; start < pos; start++) {
			if (!(readBuffer[start] == 0x20 || readBuffer[start] == 0x9)) {
				break;
			}
		}
		ASSERT_MIN_LENGTH(start + 2)
		// Check if we are ending the configuration.
		if (pos >= (start + 3) && readBuffer[start] == '/' && readBuffer[start
				+ 1] == 'C' && readBuffer[start + 2] == 'A') {
			SerialConfigEncoder::transmitter.LastPartSend();
			LOGLN("Finished configuration.");
			status = SH_IDLE;
			return;
		}
		for (byte i = 0; i < this->encoderSize; i++) {
			// See if any of the
			if (memcmp(readBuffer + start, encoders[i].type, 4) == 0) {
				// Cool, we have the matching encoder.
				encoders[i].encoder->Handle(readBuffer + start + 5, pos - start
						- 5);
				LOGLN("Handled by Encoder !");
				// Done
				return;
			}
		}
		// If we reach this part of the code, no encoder was found.
		ERRORLN("No Encoder found !");
	}
	}
}

void SerialHandler::RegisterEncoder(const byte* type,
		SerialConfigEncoder* encoder) {
	if (encoderSize == 5) {
		ERRORLN("Only space for 5 encoders is reserved. Add more space in the SerialHandler.");
		return;
	} else {
		encoders[encoderSize].type = type;
		encoders[encoderSize++].encoder = encoder;
	}

}

}
