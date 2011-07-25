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
#define ONEWIRE_CRC 1
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

#include "PinController.h"

namespace OPhomo {

typedef uint8_t DeviceAddress[8];
class OneWireSensorFactory;

class OneWirePinController: public OPhomo::PinController {
public:
	OneWirePinController(Pin* inPin);

	uint8_t Reset();

	void WriteBit(uint8_t v);
	uint8_t ReadBit(void);

	void Write(uint8_t v, uint8_t power = 0);
	uint8_t Read();

	void Select(uint8_t rom[8]);

	void Skip();

	void Depower();

#if ONEWIRE_SEARCH
	uint8_t Search( OneWireSensorFactory* factory  );

	static uint8_t crc8(uint8_t *addr, uint8_t len);
#ifdef ONEWIRE_CRC16
	unsigned short crc16(unsigned short *data, unsigned short len);
#endif
#endif

	static bool ValidAddress(DeviceAddress& deviceAddress) {
		return (crc8(deviceAddress, 7) == deviceAddress[7]);
	}

	virtual ~OneWirePinController();
private:
	//	uint8_t bitmask;
	//	volatile uint8_t *baseReg;


};
}
#endif /* ONEWIREPINCONTROLLER_H_ */
