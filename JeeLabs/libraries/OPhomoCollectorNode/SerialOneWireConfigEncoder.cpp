/*
 * SerialOneWireConfigEncoder.cpp
 *
 *  Created on: Mar 8, 2011
 *      Author: decock
 */
#include "HardwareSerial.h"
#include "SerialOneWireConfigEncoder.h"
#include "OPhomoProtocolHeader.h"

namespace OPhomo {
const byte SerialOneWireConfigEncoder::type[] = { 'S', 'E', 'O', 'W' };
SerialOneWireConfigEncoder::SerialOneWireConfigEncoder() {

}

byte
SerialOneWireConfigEncoder::getType() {
	return ONEWIRE_SENSOR_CONFIG_TYPE;
}


void SerialOneWireConfigEncoder::EncodeSerial2Bin(byte* buffer, byte length) {
// Let's see what we got here...
	messageLength = 0;
	byte pos = 2;
	for (byte i = 0; i < length; i++) {
		switch (buffer[i]) {
		case 'p': {
			i++;
			int portId = GetInt(buffer, i);
			//@TODO do some sanity checks here
			encodedMessage[pos++] = 1; // This is the portId type.
			messageLength++;
			messageLength += EncodeInt(portId, encodedMessage, pos);
		}
			break;
		case 'a': {
			i++;
			int analog = GetInt(buffer, i);
			//@TODO do some sanity checks here
			encodedMessage[pos++] = 2; // This is the analog pin type.
			messageLength++;
			// Save is a boolean, so only 1 or 0 is returned.
			if ( analog > 0 )
				messageLength += EncodeInt(1, encodedMessage, pos);
			else
				messageLength += EncodeInt(0, encodedMessage, pos);
		}
			break;
		case 'd': {
			i++;
			int digital = GetInt(buffer, i);
			//@TODO do some sanity checks here
			encodedMessage[pos++] = 3; // This is the digital pin type.
			messageLength++;
			// Save is a boolean, so only 1 or 0 is returned.
			if ( digital > 0 )
				messageLength += EncodeInt(1, encodedMessage, pos);
			else
				messageLength += EncodeInt(0, encodedMessage, pos);
		}
			break;
		case (byte) 0x20:
		case (byte) 0x09: {
			// spaces and tabs are ignored.
		}
			break;
		case (byte) 0x0D: {
			i = length;
			break;
		}
		break;
		default:
			// Unknown entry:
			ERROR("Unknown : ");
			Serial.print(buffer[i]);
			Serial.print(" at ");
			Serial.println((int)i);
			return;
		}
	}
	encodedMessage[0] = ONEWIRE_SENSOR_CONFIG_TYPE;
	encodedMessage[1] = messageLength;
	// Send the message.
	transmitter.SetMessageType(CONFIG_ADVERTISE_TYPE);
	transmitter.Send(encodedMessage, messageLength + 2);
}

byte
SerialOneWireConfigEncoder::DecodeBin2Serial(byte* message, byte messageLength, char* serialBuffer, int* serialLength) {
	// When comming here, the SEOW header and length are already 'consumed'.
	if ( messageLength != 9 ) {
		// FAIL
		ERRORLN("SEOW::DL");
		return 0;
	}
	int pos = 1;
	byte id = message[0];
	itoa((int)id, serialBuffer, 10 );
	while ( id > 10 ) {
		id /= 10;
		pos++;
	}
	serialBuffer[pos++] = ' ';
	for ( byte i = 1; i < 9; i++ ) {
		if ( message[i] <= 16) {
			 serialBuffer[pos++] = '0';
		}
		itoa((int)message[i],serialBuffer + pos,16);
		pos++;
		if ( message[i] > 16) {
			pos++;
		}
		if ( i < 8 )
		 serialBuffer[pos++] = ':';
	}
	serialBuffer[pos++]='\0';
	*serialLength = pos;
	return 9;
}


SerialOneWireConfigEncoder::~SerialOneWireConfigEncoder() {

}

}
