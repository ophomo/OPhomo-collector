/*
 * OneWireSensorChainStub.cpp
 *
 *  Created on: 26 Aug 2011
 *      Author: OPhomo
 *
 * This OneWireSensorPin is based on the OneWire library for the Arduino ( Copyright (c) 2007, Jim Studt )
 * His code was inspired by Derek Yerger's code, so I want to honor him too.
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

#include "OneWireSensorPin.h"
#include "OneWireSensor.h"
#include "Arduino.h"
namespace OPhomo {
OneWireSensorPin::OneWireSensorPin(Pin* inPin) {
	pin = inPin;
}

OneWireSensorPin::~OneWireSensorPin() {
}

uint8_t OneWireSensorPin::Reset(void) {
	uint8_t r;
	uint8_t retries = 125;

	noInterrupts();
	pin->DirectInputMode();
	interrupts();

	// wait until the wire is high... just in case
	do {
		if (--retries == 0)
			return 0;
		delayMicroseconds(2);
	} while (!pin->DirectRead());


	noInterrupts();
	pin->DirectWrite(0);
	pin->DirectOutputMode();
	interrupts();
	delayMicroseconds(480);
	noInterrupts();
	pin->DirectInputMode();
	delayMicroseconds(70);
	r = !(pin->DirectRead());
	interrupts();
	delayMicroseconds(410);
	return r;
}

//
// Write a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
void OneWireSensorPin::WriteBit(uint8_t v) {
	if (v & 1) {
		noInterrupts();
		pin->DirectWrite(0);
		pin->DirectOutputMode();
		delayMicroseconds(10);
		pin->DirectWrite(1);
		interrupts();
		delayMicroseconds(55);
	} else {
		noInterrupts();
		pin->DirectWrite(0);
		pin->DirectOutputMode();
		delayMicroseconds(65);
		pin->DirectWrite(1);
		interrupts();
		delayMicroseconds(5);
	}
}

//
// Read a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
uint8_t OneWireSensorPin::ReadBit(void) {
	uint8_t r;

	noInterrupts();
	pin->DirectOutputMode();
	pin->DirectWrite(0);
	delayMicroseconds(3);
	pin->DirectInputMode();
	delayMicroseconds(10);
	r = pin->DirectRead();
	interrupts();
	delayMicroseconds(53);
	return r;
}
//
// Write a byte. The writing code uses the active drivers to raise the
// pin high, if you need power after the write (e.g. DS18S20 in
// parasite power mode) then set 'power' to 1, otherwise the pin will
// go tri-state at the end of the write to avoid heating in a short or
// other mishap.
//
void OneWireSensorPin::Write(uint8_t v, uint8_t power /* = 0 */) {
	uint8_t bitMask;

	for (bitMask = 0x01; bitMask; bitMask <<= 1) {
		WriteBit((bitMask & v) ? 1 : 0);
	}
	if (!power) {
		noInterrupts();
		pin->DirectInputMode();
		pin->DirectWrite(0);
		interrupts();
	}
}

//
// Read a byte
//
uint8_t OneWireSensorPin::Read() {
	uint8_t bitMask;
	uint8_t r = 0;

	for (bitMask = 0x01; bitMask; bitMask <<= 1) {
		if (ReadBit())
			r |= bitMask;
	}
	return r;
}

//
// Do a ROM skip
//
void OneWireSensorPin::Skip() {
	Write(0xCC); // Skip ROM
}

void OneWireSensorPin::Depower() {
	noInterrupts();
	pin->DirectInputMode();
	interrupts();
}

/*uint16_t OneWireSensorPin::InitReadSensor(){
	Reset();
	Skip();
	Write(STARTCONVO,  true);
	// Delay
	return 0;
}
*/

}
