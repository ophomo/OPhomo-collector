/*
 * DallasTemperatureSensor.cpp
 *
 *  Created on: Jan 31, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "DallasTemperatureSensor.h"
#include "TemperatureSensorMeasurement.h"
#include "string.h"

// 273.15 << 4
#define KELVIN_C_OFFSET 4370
namespace OPhomo {

uint8_t* DallasTemperatureSensor::scratchPad = new uint8_t[9];

DallasTemperatureSensor::DallasTemperatureSensor( OneWireSensorPin* inPin, DeviceAddress& inAddress) :
	OneWireSensor(inPin, inAddress) {
	if (deviceAddress[0] != DS18S20MODEL) {
		scratchPad[CONFIGURATION] = TEMP_12_BIT;
		WriteScratchPad(true);
	}
}

uint16_t DallasTemperatureSensor::GetConversionDelay() {
	uint8_t scaledResult;
	if (deviceAddress[0] == DS18S20MODEL)
		scaledResult = TEMP_12_BIT;
	else {
		// For the moment, we use a fixed TEMP_13_BIT;
		scaledResult = TEMP_12_BIT;
/*		ReadScratchPad();
		scaledResult = scratchPad[CONFIGURATION]; */
	}
	return (94 << ((scaledResult - TEMP_9_BIT) >> 5));
}
/*
 bool DallasTemperatureSensor::isConnected() {
 ReadScratchPad();
 return OneWirePinController::crc8(scratchPad, 8)
 == scratchPad[SCRATCHPAD_CRC];
 }*/

#ifdef DALLAS_RESOLUTION
uint8_t DallasTemperatureSensor::GetResolution() {
	if (deviceAddress[0] == DS18S20MODEL)
	return 9; // this model has a fixed resolution

	ReadScratchPad();
	switch (scratchPad[CONFIGURATION]) {
		case TEMP_12_BIT:
		return 12;
		break;
		case TEMP_11_BIT:
		return 11;
		break;
		case TEMP_10_BIT:
		return 10;
		break;
		case TEMP_9_BIT:
		return 9;
		break;
	}
	return 9;
}

// set resolution of a device to 9, 10, 11, or 12 bits
void DallasTemperatureSensor::SetResolution(uint8_t newResolution) {
	if (this->isConnected()) {
		// DS18S20 has a fixed 9-bit resolution
		if (deviceAddress[0] != DS18S20MODEL) {
			switch (newResolution) {
				case 12:
				scratchPad[CONFIGURATION] = TEMP_12_BIT;
				break;
				case 11:
				scratchPad[CONFIGURATION] = TEMP_11_BIT;
				break;
				case 10:
				scratchPad[CONFIGURATION] = TEMP_10_BIT;
				break;
				case 9:
				default:
				scratchPad[CONFIGURATION] = TEMP_9_BIT;
				break;
			}
			WriteScratchPad(false);
		}
	}
}
#endif

void DallasTemperatureSensor::Read(MeasurementHandler* handler) {
	pin->Reset();
	Select();
	pin->Write(STARTCONVO, true);
	delay(750);
	ReadNow(handler);

}

void DallasTemperatureSensor::ReadNow(MeasurementHandler* handler) {
	ReadScratchPad();
	uint8_t crc = 0;
	uint8_t len = 8;
	uint8_t* addr = scratchPad;

	while (len--) {
		uint8_t inbyte = *addr++;
		for (uint8_t i = 8; i; i--) {
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix)
				crc ^= 0x8C;
			inbyte >>= 1;
		}
	};

	int16_t rawTemperature = 0;

	if (crc == scratchPad[SCRATCHPAD_CRC])
		rawTemperature = (((int16_t) scratchPad[TEMP_MSB]) << 8)
				| scratchPad[TEMP_LSB];

	// K = C + 273
	switch (deviceAddress[0]) {
	case DS18B20MODEL:
	case DS1822MODEL:
		rawTemperature += (uint16_t) KELVIN_C_OFFSET;
		rawTemperature <<= 2;
		break;
	case DS18S20MODEL:
		/*
		 Resolutions greater than 9 bits can be calculated using the data from
		 the temperature, COUNT REMAIN and COUNT PER �C registers in the
		 scratchpad. Note that the COUNT PER �C register is hard-wired to 16
		 (10h). After reading the scratchpad, the TEMP_READ value is obtained
		 by truncating the 0.5�C bit (bit 0) from the temperature data. The
		 extended resolution temperature can then be calculated using the
		 following equation:

		 COUNT_PER_C - COUNT_REMAIN
		 TEMPERATURE = TEMP_READ - 0.25 + --------------------------
		 COUNT_PER_C
		 */

		// Good spot. Thanks Nic Johns for your contribution
		rawTemperature = (rawTemperature >> 1) << 6;
		// Now, we still need the rest
		float rest = 64 * (-0.25 + ((float) (scratchPad[COUNT_PER_C]
				- scratchPad[COUNT_REMAIN]) / (float) scratchPad[COUNT_PER_C]));
		rawTemperature += (int) (rest);
		break;
	}
	TemperatureSensorMeasurement result;
	result.Set(rawTemperature);
	handler->Handle(result);
}

DallasTemperatureSensor::~DallasTemperatureSensor() {
	// TODO Auto-generated destructor stub
}
;

}
