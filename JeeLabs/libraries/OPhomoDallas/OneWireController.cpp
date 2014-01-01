/*
 * OneWireController.cpp
 *
 *  Created on: Mar 13, 2011
 *      Author: decock
 */
#include "OneWireController.h"
#include "SensorNode.h"
#include "OneWireSensor.h"
#include "ConsoleMeasurementHandler.h"
#include "OneWireStructures.h"

namespace OPhomo {

OneWireController::OneWireController(SensorNode& node) :
	ConfigurationController(node) {
	node.Register(this);
	for (unsigned int i = 0; i < MAX_DALLAS_PLUGS; i++) {
		dallasPlugs[i] = NULL;
	}
}

byte OneWireController::HandleConfig(byte* message, byte length) {
	//	DallasPlug* nullPlug = NULL;
	DallasPlug* plug = NULL;
	byte pos;
	for (pos = 0; pos < length; pos++) {
		Serial.print("P:");
		Serial.println((int) pos);
		switch (message[pos]) {
		case 0x01: {
			int portId = 0;
			byte decodedLength = ConfigurationController::DecodeInt(
					message + pos + 1, length - pos - 2, portId);
			if (decodedLength == 0) {
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
				default: {
				}

				}
				if (port) {
					// If we have a port, we can do something.
					if (plug == NULL) {
						plug = new DallasPlug(port);
						dallasPlugs[portId - 1] = plug;
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
			// Digital pin.
			int digital = 0;
			byte decodedLength = ConfigurationController::DecodeInt(
					message + pos + 1, length - pos - 2, digital);
			if (decodedLength == 0) {
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
			Serial.print("OneWire::Unknown item : ");
			Serial.println((int) message[pos]);
		}
		}
	}
	return pos;
}

byte OneWireController::ConfigReply() {
	byte pos = 0;
	OneWireConfigReply reply;
	reply.state = 1;
	reply.id.value = 0;

	// First, search all OneWire
	for (byte i = 0; i < MAX_DALLAS_PLUGS; i++) {
		if (this->dallasPlugs[i] != NULL) {
			// Set the port
			reply.id.port = reply.port_port = i;
			byte nrOfSensors = dallasPlugs[i]->Search();
			/*
			 * Each sensor will be encoded as:
			 * _________________________________
			 * |   0   |   1   |   2   |   3   |
			 * =================================
			 * |  SEOW |  L    |  ST:1 |  id   |
			 * | port  |       ADDRESS OF      |
			 * |        SENSOR                 |
			 * |       |
			 * Where :
			 * SEOW is the type of the message.
			 * L  is the length being 7 bytes.
			 * id is the id used for the sensor.
			 * port is the port ( 4 bits ) and pin ( 2 bits ).
			 * ADDRESS OF SENSOR is the physical hardware address of the sensor.
			 */
			reply.id.pin = reply.port_pin = ANALOG;
			for (byte j = 0; j < nrOfSensors; j++) {
				OneWireSensor* sensor = dallasPlugs[i]->analogSensor(j);
				if (sensor) {
					reply.id.value = j;
					// Now, append the address;
					byte* address = sensor->GetDeviceAddress();
					for (byte k = 0; k < sizeof(DeviceAddress); k++) {
						reply.address[k] = address[k];
					}
					sensorNode->rf12Transmitter.Send((byte*) (&reply),
							sizeof(OneWireConfigReply));
				}
			}
			reply.id.pin = reply.port_pin = DIGITAL;
			for (byte j = 0; j < nrOfSensors; j++) {
				OneWireSensor* sensor = dallasPlugs[i]->digitalSensor(j);
				if (sensor) {
					reply.id.value = j;
					// Now, append the address;
					byte* address = sensor->GetDeviceAddress();
					for (byte k = 0; k < sizeof(DeviceAddress); k++) {
						reply.address[k] = address[k];
					}
					sensorNode->rf12Transmitter.Send((byte*) (&reply),
							sizeof(OneWireConfigReply));
				}
			}
		}
	}
	return pos;
}

// Helper class

class OneWireMeasurementHandler: public MeasurementHandler {
public:
	OneWireMeasurementHandler(byte type, RF12Concatenator& concatenator) :
		rf12(&concatenator) {
		message[0] = type;
		// 		message[1] is the length
		message[2] = 2; // Report type
	}
	;

	/**
	 * This will store the measurement in a Type Length Value encoding.
	 * @param measurement Measurement which will be stored.
	 */
	uint8_t Handle(SensorMeasurement& measurement) {
		/**
		 * We report for each temperature this:
		 * _________________________________
		 * |   0   |   1   |   2   |   3   |
		 * =================================
		 * |  SEOW |   L   |  ST=2 |  id   |
		 * |   MT  |  L:2  |   Measurement |
		 *
		 * Where
		 *  SEOW is the type
		 *  ST: 2 : This is a report
		 *  L is the lenght, for temperature this is 5.
		 *  id is the ID of the sensor.
		 *  MT is the Measurement type ( Temperature, .... )
		 *  L is the length, normally 2
		 *  Measurement is ...
		 *
		 */
		memcpy(message + 3, &id, 1);
		++(id.value);
		uint8_t innerSize = measurement.getSize();
		uint8_t totalLenght = innerSize + 4;
		message[1] = totalLenght;
		if (totalLenght <= maxSize - 2) {
			message[4] = measurement.getType();
			message[5] = innerSize;
			measurement.toBytes(message + 6);
			// Send out this message
			rf12->Send(message, totalLenght + 2);
			return totalLenght;
		} else {
			Serial.println("RF12Measurement::Failed::Message to long.");
			Serial.println(totalLenght);
			return 0;
		}
	}

	virtual ~OneWireMeasurementHandler() {
	}

	// We have made this one public, because it will be 'tweaked'
	OneWireID id;
protected:
	const static uint8_t maxSize = 10;
	byte message[maxSize];
	RF12Concatenator* rf12;
};

byte OneWireController::Perform() {
	//ConsoleMeasurementHandler handler;
	// -- Measure and send.
	OneWireMeasurementHandler rf12Handler(getType(),
			sensorNode->rf12Transmitter);
	// We start reading all the sensors.
	// Start initiating
	uint16_t time2wait = 0;
	for (byte plug = 0; plug < MAX_DALLAS_PLUGS; plug++) {
		if (this->dallasPlugs[plug] != NULL) {
			uint16_t ttw = dallasPlugs[plug]->InitReadAll();
			time2wait = ((ttw > time2wait) ? ttw : time2wait);
		}
	}
	while (time2wait) {
		time2wait = 0;
		for (byte plug = 0; plug < MAX_DALLAS_PLUGS; plug++) {
			if (this->dallasPlugs[plug] != NULL) {
				rf12Handler.id.value = 0;
				rf12Handler.id.port = plug;
				rf12Handler.id.pin = ANALOG;
				time2wait += dallasPlugs[plug]->ReadAllAnalogSensors(
						&rf12Handler);
				rf12Handler.id.pin = DIGITAL;
				time2wait += dallasPlugs[plug]->ReadAllDigitalSensors(
						&rf12Handler);
			}
		}
	}
	return 1;
}

OneWireController::~OneWireController() {
	// TODO Auto-generated destructor stub
}

}
