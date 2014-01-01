/*
 * OneWirePinController.h
 *
 *  Created on: Jan 28, 2011
 *      Author: dd@ophomo.org
 *
 */

#ifndef ONEWIREPINCONTROLLER_H_
#define ONEWIREPINCONTROLLER_H_

// you can exclude onewire_search by defining that to 0
#ifndef ONEWIRE_SEARCH
#define ONEWIRE_SEARCH 1
#endif

// You can exclude CRC checks altogether by defining this to 0
#ifndef ONEWIRE_CRC
#define ONEWIRE_CRC 0
#endif

// Select the table-lookup method of computing the 8-bit CRC
// by setting this to 1.  The lookup table no longer consumes
// limited RAM, but enlarges total code size by about 250 bytes
#ifndef ONEWIRE_CRC8_TABLE
#define ONEWIRE_CRC8_TABLE 0
#endif

// You can allow 16-bit CRC checks by defining this to 1
// (Note that ONEWIRE_CRC must also be 1.)
#ifndef ONEWIRE_CRC16
#define ONEWIRE_CRC16 0
#endif

#include "OneWireSensor.h"
#include "MeasurementHandler.h"
#include "MilliTimer.h"

namespace OPhomo {

class OneWirePinController {
public:
	OneWirePinController(OneWireSensorPin* inPin);

	uint16_t InitSensorRead(byte pos);

	uint16_t SensorRead(MeasurementHandler* handler);

	uint16_t InitSensorReadAll();

	uint16_t SensorReadAll(MeasurementHandler* handler);


	OneWireSensor* operator[](uint8_t i) {
		if (list) {
			return (*list)[i];
		}
		return NULL;
	}

	uint8_t NumberOfSensors() {
		return nrOfSensors;
	}

	uint8_t Search();

#if ONEWIRE_CRC8
	static uint8_t crc8(uint8_t *addr, uint8_t len);
#endif
#if ONEWIRE_CRC16
	unsigned short crc16(unsigned short *data, unsigned short len);
#endif

#if ONEWIRE_VALIDADDRESS
	static bool ValidAddress(DeviceAddress& deviceAddress) {
		return (crc8(deviceAddress, 7) == deviceAddress[7]);
	}
#endif

	virtual ~OneWirePinController();
private:
	OneWireSensorPin* pin;
	OneWireSensorListItem* list;

	//	OneWireSensorChainInterface* pin;
	uint8_t nrOfSensors;

	MilliTimer readTimer;
	byte readPos;

};
}
#endif /* ONEWIREPINCONTROLLER_H_ */
