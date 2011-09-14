/*
 * DallasTemperatureSensor.h
 *
 *  Created on: Jan 31, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef DALLASTEMPERATURESENSOR_H_
#define DALLASTEMPERATURESENSOR_H_

#include "OneWireSensor.h"
#include "wiring.h"
// Model IDs
#define DS18S20MODEL 0x10
#define DS18B20MODEL 0x28
#define DS1822MODEL  0x22

// Scratchpad locations
#define TEMP_LSB        0
#define TEMP_MSB        1
#define HIGH_ALARM_TEMP 2
#define LOW_ALARM_TEMP  3
#define CONFIGURATION   4
#define INTERNAL_BYTE   5
#define COUNT_REMAIN    6
#define COUNT_PER_C     7
#define SCRATCHPAD_CRC  8

// Device resolution
#define TEMP_9_BIT  0x1F //  9 bit
#define TEMP_10_BIT 0x3F // 10 bit
#define TEMP_11_BIT 0x5F // 11 bit
#define TEMP_12_BIT 0x7F // 12 bit

namespace OPhomo {

class DallasTemperatureSensor:  public OneWireSensor {
public:
	DallasTemperatureSensor(OneWireSensorChainInterface* inWrappee, DeviceAddress& address);

	bool isParasite() {
		return ReadPowerSupply();
	}

#ifdef DALLAS_GETRESOLUTION
	uint8_t GetResolution();

	// set resolution of a device to 9, 10, 11, or 12 bits
	void SetResolution(uint8_t newResolution);
#endif

	virtual void ReadSensor(MeasurementHandler* handler);

	virtual ~DallasTemperatureSensor();

protected:
	virtual uint8_t GetConversionDelay();

	static uint8_t* scratchPad;

	void ReadScratchPad() {
		// send the command
		wrappee->Reset();
		Select();
		wrappee->Write(READSCRATCH);

		// read the response

		// byte 0: temperature LSB
		scratchPad[TEMP_LSB] = wrappee->Read();

		// byte 1: temperature MSB
		scratchPad[TEMP_MSB] = wrappee->Read();

		// byte 2: high alarm temp
		scratchPad[HIGH_ALARM_TEMP] = wrappee->Read();

		// byte 3: low alarm temp
		scratchPad[LOW_ALARM_TEMP] = wrappee->Read();

		// byte 4:
		// DS18S20: store for crc
		// DS18B20 & DS1822: configuration register
		scratchPad[CONFIGURATION] = wrappee->Read();

		// byte 5:
		// internal use & crc
		scratchPad[INTERNAL_BYTE] = wrappee->Read();

		// byte 6:
		// DS18S20: COUNT_REMAIN
		// DS18B20 & DS1822: store for crc
		scratchPad[COUNT_REMAIN] = wrappee->Read();

		// byte 7:
		// DS18S20: COUNT_PER_C
		// DS18B20 & DS1822: store for crc
		scratchPad[COUNT_PER_C] = wrappee->Read();

		// byte 8:
		// SCTRACHPAD_CRC
		scratchPad[SCRATCHPAD_CRC] = wrappee->Read();

		wrappee->Reset();
	}

	void WriteScratchPad(bool parasite) {
		wrappee->Reset();
		Select();
		wrappee->Write(WRITESCRATCH);
		//Currently we don't use the alarms, but if you want, you need to do it here...
		//		pinController->Write(scratchPad[HIGH_ALARM_TEMP]); // high alarm temp
		//		pinController->write(scratchPad[LOW_ALARM_TEMP]); // low alarm temp
		// DS18S20 does not use the configuration register
		if (deviceAddress[0] != DS18S20MODEL)
			wrappee->Write(scratchPad[CONFIGURATION]); // configuration
		wrappee->Reset();
		// save the newly written values to eeprom
		wrappee->Write(COPYSCRATCH, parasite);
		if (parasite)
			delay(10); // 10ms delay
		wrappee->Reset();
	}

	bool ReadPowerSupply() {
		bool ret = false;
		wrappee->Reset();
		Select();
		wrappee->Write(READPOWERSUPPLY);
		if (wrappee->ReadBit() == 0)
			ret = true;
		wrappee->Reset();
		return ret;
	}

};

}

#endif /* DALLASTEMPERATURESENSOR_H_ */
