/*
 * OneWireSensorChainInterface.h
 *
 *  Created on: 26 Aug 2011
 *      Author: OPhomo
 */

#ifndef ONEWIRESENSORCHAININTERFACE_H_
#define ONEWIRESENSORCHAININTERFACE_H_
#include "stdint.h"
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
class OneWireSensor;

class OneWireSensorChainInterface {
public:
	OneWireSensorChainInterface();

	// The low level methods, implemented by the OneWirePin.
	virtual uint8_t Reset() = 0;

	virtual void WriteBit(uint8_t v) = 0;

	virtual uint8_t ReadBit(void) = 0;

	virtual void Write(uint8_t v, uint8_t power = 0) = 0;

	virtual uint8_t Read() = 0;

	virtual void Skip() = 0;

	virtual void Depower() = 0;

	virtual uint8_t InitReadSensor() = 0;

	virtual void ReadSensor(MeasurementHandler* handler) = 0;

	virtual OneWireSensor* operator[] (uint8_t) = 0;

	virtual ~OneWireSensorChainInterface();
protected:
};
}
#endif /* ONEWIRESENSORCHAININTERFACE_H_ */
