/*
 * OPhomoCollectorNode.pde
 *
 *  Created on: Feb 18, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#define OPHOMO_COLLECTORNODE 1
#include "WProgram.h"
#include "JeeLink.h"
#include "CollectorNode.h"
#include "SerialHandler.h"
#include "SerialRF12ConfigEncoder.h"
#include "SerialOneWireConfigEncoder.h"

#define VERSION "0.2.2"

using namespace OPhomo;

CollectorNode node;
SerialHandler serialHandler;
SerialRF12ConfigEncoder rf12encoder;
SerialOneWireConfigEncoder oneWireEncoder;

void printAction(const char* action, byte inNode) {
	Serial.print(action);
	Serial.println((int) inNode);
}

void CollectorNode::handleConfigSolicit(byte inNode) {
	// Here, we will need to send a reply base on the information we have on this node.
	// To get this information from the application, we send the request on the Serial port interface.
	printAction("CS", inNode);
}

void CollectorNode::handleConfigAccept(byte inNode, byte* message,
		byte totalLen) {
	// Here, we will need to send a reply base on the information we have on this node.
	// To get this information from the application, we send the request on the Serial port interface.
	printAction("CY", inNode);
	// Walk the message and the decoders.
	byte len, type;
	byte pos = 0;
	char serialBuffer[64];
	int serialLength = 64;
	for (;;) {
		type = message[pos];
		len = message[pos + 1];
		LOGLN((int) type);
		LOGLN((int) len);
		if (type == 0 && len == 0)
			break;
		for (byte i = 0; i < serialHandler.data.encoderSize; i++) {
			// See if any of the encoders knows this type
			if (serialHandler.data.encoders[i].encoder-> getType() == type) {

				serialLength = 64;
				if (serialHandler.data.encoders[i].encoder->DecodeBin2Serial(
						message + pos + 2, len, serialBuffer, &serialLength)) {
					Serial.print("\t");
    				Serial.write(serialHandler.data.encoders[i].type, 4);
					Serial.print(" ");
					Serial.println(serialBuffer);
				}
			}
		}
		pos += 2 + len;
		if (pos >= totalLen) {
			Serial.print((int) pos);
			;
			Serial.print(" <-> ");
			Serial.println((int) totalLen);
			break;
		}
	}
	Serial.print("/");
	printAction("CY", inNode);
}

void CollectorNode::handleConfigReject(byte inNode, byte* message, byte len) {
	// Here, we will need to send a reply base on the information we have on this node.
	// To get this information from the application, we send the request on the Serial port interface.
	printAction("CN", inNode);
}

void setup(void) {
	Serial.begin(57600);
	Serial.print("\n[OPHOMO COLLECTOR NODE v");
	Serial.print(VERSION);
	Serial.println("]");
	node.setup();
	serialHandler.RegisterEncoder(SerialRF12ConfigEncoder::type, &rf12encoder);
	serialHandler.RegisterEncoder(SerialOneWireConfigEncoder::type,
			&oneWireEncoder);

}

void loop(void) {
	node.loop();
	serialHandler.Try();
}

int main(void) {

	/* Must call init for arduino to work properly */
	init();

	/****************************/
	/* Add your setup code here */
	/****************************/
	setup();

	for (;;) {

		loop();

	} // end for

} // end main

