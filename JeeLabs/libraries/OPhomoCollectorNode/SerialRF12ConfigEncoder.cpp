/*
 * SerialRF12ConfigEncoder.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "HardwareSerial.h"
#include "SerialRF12ConfigEncoder.h"
#include "OPhomoProtocolHeader.h"

#define RF12_NODEID_TYPE 1
#define RF12_GROUPID_TYPE 2
#define RF12_BAND_TYPE 3

namespace OPhomo {
const byte SerialRF12ConfigEncoder::type[] = { 'R', 'F', '1', '2' };

SerialRF12ConfigEncoder::SerialRF12ConfigEncoder() {
}


byte
SerialRF12ConfigEncoder::getType() {
	return RF12_CONFIG_TYPE;
}

void SerialRF12ConfigEncoder::EncodeSerial2Bin(byte* buffer, byte length) {
	// Let's see what we got here...
	messageLength = 0;
	byte pos = 2;
	for (byte i = 0; i < length; i++) {
		switch (buffer[i]) {
		case 'n': {
			i++;
			int nodeId = GetInt(buffer, i);
			//@TODO do some sanity checks here
			encodedMessage[pos++] = 1; // This is the nodeId type.
			messageLength++;
			messageLength += EncodeInt(nodeId, encodedMessage, pos);
		}
			break;
		case 'g': {
			i++;
			int groupId = GetInt(buffer, i);
			//@TODO do some sanity checks here
			encodedMessage[pos++] = 2; // This is the groupId type.
			messageLength++;
			messageLength += EncodeInt(groupId, encodedMessage, pos);
		}
			break;
		case 'b': {
			i++;
			int band = GetInt(buffer, i);
			//@TODO do some sanity checks here
			encodedMessage[pos++] = 3; // This is the band type.
			messageLength++;
			messageLength += EncodeInt(band, encodedMessage, pos);
		}
			break;
		case 's': {
			i++;
			int save = GetInt(buffer, i);
			//@TODO do some sanity checks here
			encodedMessage[pos++] = 4; // This is the band type.
			messageLength++;
			// Save is a boolean, so only 1 or 0 is returned.
			if ( save > 0 )
				messageLength += EncodeInt(1, encodedMessage, pos);
			else
				messageLength += EncodeInt(0, encodedMessage, pos);
		}
		case (byte) 0x20:
		case (byte) 0x09: {
			// spaces and tabs are ignored.
		}
			break;
		case (byte) 0x0D: {
//			LOGLN("Found a end-of-line.");
			// Force quiting the loop.
	/*		Serial.print(" at ");
			Serial.println((int)i);
			Serial.print(" with length ");
			Serial.println((int)length);*/

			i = length;
			break;

		}
		break;
		default:
			// Unknown entry:
			ERROR("Unknown:");
			Serial.print(buffer[i]);
			Serial.print(" P:");
			Serial.println((int)i);
			return;
		}
	}
	encodedMessage[0] = RF12_CONFIG_TYPE;
	encodedMessage[1] = messageLength;
	Serial.print("EM L:");
	Serial.println((int) messageLength);
	// Send the message.
	transmitter.SetMessageType(CONFIG_ADVERTISE_TYPE);
	transmitter.Send(encodedMessage, messageLength + 2);
}

SerialRF12ConfigEncoder::~SerialRF12ConfigEncoder() {

}

}
