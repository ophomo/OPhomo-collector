/*
 * OneWireSensor.h
 *
 *  Created on: Feb 6, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef ONEWIRESENSOR_H_
#define ONEWIRESENSOR_H_

#include "OneWireSensorPin.h"
#include "MeasurementHandler.h"

#define FALSE 0
#define TRUE  1

// OneWire commands
#define STARTCONVO      0x44  // Tells device to take a reading and put it on the scratchpad
#define COPYSCRATCH     0x48  // Copy EEPROM
#define READSCRATCH     0xBE  // Read EEPROM
#define WRITESCRATCH    0x4E  // Write to EEPROM
#define RECALLSCRATCH   0xB8  // Reload from last known
#define READPOWERSUPPLY 0xB4  // Determine if device needs parasite power
#define ALARMSEARCH     0xEC  // Query bus for devices with an alarm condition



namespace OPhomo {

typedef uint8_t DeviceAddress[8];

class OneWireSensor {
public:
	OneWireSensor(	OneWireSensorPin* pin, DeviceAddress& deviceAddress);

	virtual bool isParasite() = 0;

	virtual void Read(MeasurementHandler* handler) = 0;

	virtual void ReadNow(MeasurementHandler* handler) = 0;

	uint8_t* GetDeviceAddress() {
		return deviceAddress;
	}

	virtual ~OneWireSensor();

	void Select();

	virtual uint16_t GetConversionDelay() = 0;


protected:

	DeviceAddress deviceAddress;

	OneWireSensorPin* pin;
};


class OneWireSensorListItem {
public:
	OneWireSensorListItem(OneWireSensor* isensor, OneWireSensorListItem* inext = NULL) :
		next(inext), sensor(isensor) {
	}
	;

	OneWireSensor* operator[](uint8_t id) {
		// We could do this in an recursive way, but recursive is not the best way for
		// an arduino.
		OneWireSensorListItem* it = this;
		while (id && it) {
			--id;
			it = it->next;
		}
		// If it exists, return the element there.
		// else, return NULL;
		if (it)
			return it->sensor;
		else
			return NULL;
	}

	void Cleanup() {
		if ( sensor )
			delete sensor;
		if ( next )
			next->Cleanup();
		delete this;
	}


protected:
	OneWireSensorListItem* next;
	OneWireSensor* sensor;
};


}

#endif /* ONEWIRESENSOR_H_ */
