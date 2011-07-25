/*
 * DallasTemperatureSensor.cpp
 *
 *  Created on: Jan 31, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "DallasTemperatureSensor.h"
#include "string.h"

// 273.15 << 4
#define KELVIN_C_OFFSET 4370
namespace OPhomo {

uint8_t* DallasTemperatureSensor::scratchPad = new uint8_t[9];

DallasTemperatureSensor::DallasTemperatureSensor() :
	TemperatureSensor(), OneWireSensor() {
	pinController = NULL;
}

void DallasTemperatureSensor::Initialize(OneWirePinController* pinController,
		DeviceAddress& deviceAddress) {
	this->pinController = pinController;
	memcpy(this->deviceAddress, &deviceAddress, 8);
}

uint8_t DallasTemperatureSensor::GetConversionDelay() {
	if (deviceAddress[0] == DS18S20MODEL)
		return TEMP_12_BIT;
	ReadScratchPad();
	return scratchPad[CONFIGURATION];
}

bool DallasTemperatureSensor::isConnected() {
	ReadScratchPad();
	return OneWirePinController::crc8(scratchPad, 8)
			== scratchPad[SCRATCHPAD_CRC];
}

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

void DallasTemperatureSensor::RequestTemperatures() {
	bool parasite = false; //isParasite();
	pinController->Reset();
	pinController->Select(deviceAddress);
	pinController->Write(STARTCONVO, parasite);

	switch (GetConversionDelay()) {
	case TEMP_9_BIT:
		delay(94);
		break;
	case TEMP_10_BIT:
		delay(188);
		break;
	case TEMP_11_BIT:
		delay(375);
		break;
	case TEMP_12_BIT:
	default:
		delay(750);
		break;
	}
}

TemperatureSensorData DallasTemperatureSensor::ReadTemperature() {
	ReadScratchPad();
	int16_t rawTemperature = (((int16_t) scratchPad[TEMP_MSB]) << 8)
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
	TemperatureSensorData result;
	result.Set(rawTemperature);
	return result;
}

DallasTemperatureSensor::~DallasTemperatureSensor() {
	// TODO Auto-generated destructor stub
}
;

}
