/*
 * OneWireController.cpp
 *
 *  Created on: Mar 13, 2011
 *      Author: decock
 */
#include "OneWireController.h"
#include "SensorNode.h"
namespace OPhomo {

OneWireController::OneWireController(SensorNode& node) :
	ConfigurationController(node) {
	node.Register(this);
	for (unsigned int i = 0; i < MAX_DALLAS_PLUGS; i++) {
		dallasPlugs[i] = NULL;
	}
}

byte OneWireController::Handle(byte* message, byte length) {
	DallasPlug* nullPlug = NULL;
	DallasPlug*& plug = nullPlug;

	byte pos;
	for (pos = 0; pos < length; pos++) {
		Serial.print("Pos : ");
		Serial.println((int) pos);
		switch (message[pos]) {
		case 0x01: {
			int portId = 0;
			byte decodedLength = ConfigurationController::DecodeInt(
					message + pos + 1, length - pos - 2, portId);
			if (decodedLength == 0) {
				Serial.println("Decoding error in OneWireController::portID");
				return 0;
			} else {
				pos += decodedLength;
				JeePort* port = NULL;
				switch (portId) {
				case 1:
					port = &(sensorNode->getPort1());
					plug = dallasPlugs[0];
					break;
				case 2:
					port = &(sensorNode->getPort2());
					plug = dallasPlugs[1];
					break;
				case 3:
					port = &(sensorNode->getPort3());
					plug = dallasPlugs[2];
					break;
				case 4:
					port = &(sensorNode->getPort4());
					plug = dallasPlugs[3];
					break;
				default:
					Serial.println("Invalid portId ");
				}
				if (port) {
					// If we have a port, we can do something.
					if (plug == NULL) {
						plug = new DallasPlug(port);
					}
				}
			}
		}
			break;
		case 0x02: {
			// Analog pin.
			int analog = 0;
			byte decodedLength = ConfigurationController::DecodeInt(
					message + pos + 1, length - pos - 2, analog);
			if (decodedLength == 0) {
				Serial.println("Decoding error in OneWire::analog");
				return 0;
			} else {
				if (plug) {

					if (analog > 0) {
						plug->EnableAnalogPin();
					} else {
						plug->DisableAnalogPin();
					}
					pos += decodedLength;
				}
			}
		}
			break;
		case 0x03: {
			// Analog pin.
			int digital = 0;
			byte decodedLength = ConfigurationController::DecodeInt(
					message + pos + 1, length - pos - 2, digital);
			if (decodedLength == 0) {
				Serial.println("Decoding error in OneWire::digital");
				return 0;
			} else {
				if (plug) {
					if (digital > 0) {
						plug->EnableDigitalPin();
					} else {
						plug->DisableDigitalPin();
					}
					pos += decodedLength;
				}
			}
		}
			break;
		default: {
			Serial.print("OneWireController::Unknown item : ");
			Serial.println((int) message[pos]);
		}
		}
	}
	return pos;
}

byte OneWireController::ConfigReply() {
	byte pos = 0;
	byte sensorId = 1;
	byte message[sizeof(DeviceAddress) + 1];
	for (byte i = 0; i < MAX_DALLAS_PLUGS; i++) {
		if (this->dallasPlugs[i] != NULL) {
			dallasPlugs[i]->Search();
			byte nrOfSensors = dallasPlugs[i]->GetDeviceCount();
			OneWireSensor** sensors = dallasPlugs[i]->GetSensors();
			for (byte j = 0; j < nrOfSensors; j++) {
				// We should return that.
				message[0] = sensorId++;
				// Now, append the address;
				byte* address = sensors[j]->GetDeviceAddress();
				for (byte k = 0; k < sizeof(DeviceAddress); k++) {
					message[k+1] = address[k];
				}
				// Send the message.
				sensorNode->rf12Transmitter.Send (message, sizeof(DeviceAddress) + 1);
			}
		}
	}
	return pos;
}

OneWireController::~OneWireController() {
	// TODO Auto-generated destructor stub
}

}
