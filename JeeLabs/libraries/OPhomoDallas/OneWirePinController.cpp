/*
 * OneWirePinController.cpp
 *
 *  Created on: Jan 28, 2011
 *      Author: dd@ophomo.org
 *
 *
 * Currently, this is just what the standard arduino library does. But I will change this, and move this very performing code
 * as base for the Pin.
 *  This OneWirePinController is based on the OneWire library for the Arduino ( Copyright (c) 2007, Jim Studt )
 *  His code was inspired by Derek Yerger's code, so I want to honor him too.
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *  The CRC code was excerpted and inspired by the Dallas Semiconductor
 * sample code bearing this copyright.
 //---------------------------------------------------------------------------
 // Copyright (C) 2000 Dallas Semiconductor Corporation, All Rights Reserved.
 //
 // Permission is hereby granted, free of charge, to any person obtaining a
 // copy of this software and associated documentation files (the "Software"),
 // to deal in the Software without restriction, including without limitation
 // the rights to use, copy, modify, merge, publish, distribute, sublicense,
 // and/or sell copies of the Software, and to permit persons to whom the
 // Software is furnished to do so, subject to the following conditions:
 //
 // The above copyright notice and this permission notice shall be included
 // in all copies or substantial portions of the Software.
 //
 // THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 // OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 // MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 // IN NO EVENT SHALL DALLAS SEMICONDUCTOR BE LIABLE FOR ANY CLAIM, DAMAGES
 // OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 // ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 // OTHER DEALINGS IN THE SOFTWARE.
 //
 // Except as contained in this notice, the name of Dallas Semiconductor
 // shall not be used except as stated in the Dallas Semiconductor
 // Branding Policy.
 //--------------------------------------------------------------------------
 */

#include "OneWirePinController.h"
#include "OneWireSensor.h"
#include "pins_arduino.h"
#include "DallasTemperatureSensor.h"

//#include "HardwareSerial.h"

extern "C" {
#include "WConstants.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
}

namespace OPhomo {
OneWirePinController::OneWirePinController(OneWireSensorPin* inPin) {
	pin = inPin;
}


//
// Perform a search. If this function returns a '1' then it has
// enumerated the next device and you may retrieve the ROM from the
// OneWire::address variable. If there are no devices, no further
// devices, or something horrible happens in the middle of the
// enumeration then a 0 is returned.  If a new device is found then
// its address is copied to newAddr.  Use OneWire::reset_search() to
// start over.
//
// --- Replaced by the one from the Dallas Semiconductor web site ---
//--------------------------------------------------------------------------
// Perform the 1-Wire Search Algorithm on the 1-Wire bus using the existing
// search state.
uint8_t OneWirePinController::Search() {
	// global search state
	unsigned char ROM_NO[8];
	uint8_t LastDiscrepancy;
	uint8_t LastFamilyDiscrepancy;
	uint8_t LastDeviceFlag;
	uint8_t id_bit_number;
	uint8_t last_zero, rom_byte_number;
	uint8_t id_bit, cmp_id_bit;

	unsigned char rom_byte_mask, search_direction;

	// First, we need to reset everything.
	LastDiscrepancy = 0;
	LastDeviceFlag = FALSE;
	LastFamilyDiscrepancy = 0;
	for (int i = 7;; i--) {
		ROM_NO[i] = 0;
		if (i == 0)
			break;
	}
	// The number of devices found during our discovery.
	uint8_t found = 0;
	while (1) {
//		Serial.println((int)found);
		// initialize for search
		id_bit_number = 1;
		last_zero = 0;
		rom_byte_number = 0;
		rom_byte_mask = 1;
		// if the last call was not the last one
		// 1-Wire reset
		if (!pin->Reset()) {
			// Stop and return;
			return found;
//			Serial.println("RESET FAILED");
		}
		// issue the search command
		pin->Write(0xF0);
		// loop to do the search
		do {
			// read a bit and its complement
			id_bit = pin->ReadBit();
			cmp_id_bit = pin->ReadBit();

			// check for no devices on 1-wire
			if ((id_bit == 1) && (cmp_id_bit == 1))
				break;
			else {
				// all devices coupled have 0 or 1
				if (id_bit != cmp_id_bit)
					search_direction = id_bit; // bit write value for search
				else {
					// if this discrepancy if before the Last Discrepancy
					// on a previous next then pick the same as last time
					if (id_bit_number < LastDiscrepancy)
						search_direction = ((ROM_NO[rom_byte_number]
								& rom_byte_mask) > 0);
					else
						// if equal to last pick 1, if not then pick 0
						search_direction = (id_bit_number == LastDiscrepancy);

					// if 0 was picked then record its position in LastZero
					if (search_direction == 0) {
						last_zero = id_bit_number;

						// check for Last discrepancy in family
						if (last_zero < 9)
							LastFamilyDiscrepancy = last_zero;
					}
				}

				// set or clear the bit in the ROM byte rom_byte_number
				// with mask rom_byte_mask
				if (search_direction == 1)
					ROM_NO[rom_byte_number] |= rom_byte_mask;
				else
					ROM_NO[rom_byte_number] &= ~rom_byte_mask;

				// serial number search direction write bit
				pin->WriteBit(search_direction);

				// increment the byte counter id_bit_number
				// and shift the mask rom_byte_mask
				id_bit_number++;
				rom_byte_mask <<= 1;

				// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
				if (rom_byte_mask == 0) {
					rom_byte_number++;
					rom_byte_mask = 1;
				}
			}
		} while (rom_byte_number < 8); // loop until through all ROM bytes 0-7

		// if the search was successful then
		if (!(id_bit_number < 65)) {
			// search successful so set LastDiscrepancy,LastDeviceFlag,search_result
			LastDiscrepancy = last_zero;

			// check for last device
			if (LastDiscrepancy == 0)
				LastDeviceFlag = TRUE;

			if (ROM_NO[0]) {
				// Create the device from the ROM.
				switch ((int) ROM_NO[0]) {
				case DS18S20MODEL:
				case DS18B20MODEL:
				case DS1822MODEL:
					pin = new DallasTemperatureSensor(pin, ROM_NO);
					break;
				case 0:
					return found;
				//default:
					// Unknown sensor type found!
				}
				found++;
				if ( LastDeviceFlag )
					return found;
			} else
				return found;
		} else {
			return found;
		}
	}
	return 0;
}


uint8_t OneWirePinController::InitSensorRead() {
	return pin->InitReadSensor();
}

void OneWirePinController::Read(MeasurementHandler* handler) {
	pin->ReadSensor(handler);
}


#if ONEWIRE_CRC8
// The 1-Wire CRC scheme is described in Maxim Application Note 27:
// "Understanding and Using Cyclic Redundancy Checks with Maxim iButton Products"
//

#if ONEWIRE_CRC8_TABLE
// This table comes from Dallas sample code where it is freely reusable,
// though Copyright (C) 2000 Dallas Semiconductor Corporation
static const uint8_t PROGMEM dscrc_table[] = {
	0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
	157,195, 33,127,252,162, 64, 30, 95, 1,227,189, 62, 96,130,220,
	35,125,159,193, 66, 28,254,160,225,191, 93, 3,128,222, 60, 98,
	190,224, 2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
	70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89, 7,
	219,133,103, 57,186,228, 6, 88, 25, 71,165,251,120, 38,196,154,
	101, 59,217,135, 4, 90,184,230,167,249, 27, 69,198,152,122, 36,
	248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91, 5,231,185,
	140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
	17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
	175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
	50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
	202,148,118, 40,171,245, 23, 73, 8, 86,180,234,105, 55,213,139,
	87, 9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
	233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
	116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};

//
// Compute a Dallas Semiconductor 8 bit CRC. These show up in the ROM
// and the registers.  (note: this might better be done without to
// table, it would probably be smaller and certainly fast enough
// compared to all those delayMicrosecond() calls.  But I got
// confused, so I use this table from the examples.)
//
uint8_t OneWirePinController::crc8( uint8_t *addr, uint8_t len)
{
	uint8_t crc = 0;

	while (len--) {
		crc = pgm_read_byte(dscrc_table + (crc ^ *addr++));
	}
	return crc;
}
#else
//
// Compute a Dallas Semiconductor 8 bit CRC directly.
//
uint8_t OneWirePinController::crc8(uint8_t *addr, uint8_t len) {
	uint8_t crc = 0;

	while (len--) {
		uint8_t inbyte = *addr++;
		for (uint8_t i = 8; i; i--) {
			uint8_t mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix)
				crc ^= 0x8C;
			inbyte >>= 1;
		}
	}
	return crc;
}
#endif
#endif
#if ONEWIRE_CRC16
static short oddparity[16] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

//
// Compute a Dallas Semiconductor 16 bit CRC. I have never seen one of
// these, but here it is.
//
unsigned short OneWirePinController::crc16(unsigned short *data, unsigned short len)
{
	unsigned short i;
	unsigned short crc = 0;

	for ( i = 0; i < len; i++) {
		unsigned short cdata = data[len];

		cdata = (cdata ^ (crc & 0xff)) & 0xff;
		crc >>= 8;

		if (oddparity[cdata & 0xf] ^ oddparity[cdata >> 4]) crc ^= 0xc001;

		cdata <<= 6;
		crc ^= cdata;
		cdata <<= 1;
		crc ^= cdata;
	}
	return crc;
}
#endif


OneWirePinController::~OneWirePinController() {

}
;
}
