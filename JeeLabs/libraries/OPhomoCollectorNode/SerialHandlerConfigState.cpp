/*
 * SerialHandlerConfigState.cpp
 *
 *  Created on: 30 Jul 2011
 *      Author: OPhomo
 */

#include "SerialHandlerConfigState.h"
#include "SerialHandlerIdleState.h"
#include "OPhomoProtocolHeader.h"
#include "SerialHandler.h"

namespace OPhomo {

SerialHandlerConfigState::~SerialHandlerConfigState() {

}

void SerialHandlerConfigState::handle() {
	//	LOGLN("Checking in status configuring");
	// First trim spaces and tabs.
	byte start;
	for (start = 0; start < data->pos; start++) {
		if (!(data->readBuffer[start] == 0x20 || data->readBuffer[start] == 0x9)) {
			break;
		}
	}
	ASSERT_MIN_LENGTH(start + 2)
	// Check if we are ending the configuration.
	if (data->pos >= (start + 3) && data->readBuffer[start] == '/'
			&& data->readBuffer[start + 1] == 'C'
			&& data->readBuffer[start + 2] == 'A') {
		SerialConfigEncoder::transmitter.LastPartSend();
		//		LOGLN("Finished configuration.");
		serialHandler->setHandler(new SerialHandlerIdleState(serialHandler));
		return;
	}
	for (byte i = 0; i < data->encoderSize; i++) {
		// See if any of the
		if (memcmp(data->readBuffer + start, data->encoders[i].type, 4) == 0) {
			// Cool, we have the matching encoder.
			data->encoders[i].encoder->EncodeSerial2Bin(data->readBuffer + start + 5,
					data->pos - start - 5);
			//			LOGLN("Handled by Encoder !");
			// Done
			return;
		}
	}
	// If we reach this part of the code, no encoder was found.
	ERRORLN("No Encoder found :");
	ERRORLN((char*)(data->readBuffer + start));
}

SerialHandlerConfigState::SerialHandlerConfigState(SerialHandler* handler) :
	SerialHandlerState(handler) {
	INFOLN("<CONF>");
	// TODO Auto-generated constructor stub
}

}
