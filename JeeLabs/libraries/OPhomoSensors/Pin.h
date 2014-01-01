/*
 * Pin.h
 *
 *  Created on: Jan 26, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef PIN_H_
#define PIN_H_

#include <stdint.h>
#include "cpp.h"
#include "Arduino.h"

namespace OPhomo {
class Pin {
public:
	Pin(uint8_t id, bool isDigital) {
		this->id = id;
		digital = isDigital;
		inputregister = portInputRegister(digitalPinToPort(id));
		mask = digitalPinToBitMask(id);
		if (!digital)
			id += 14;
	}

	inline void InputMode() const {
		pinMode(id, INPUT);
	}
	inline void OutputMode() const {
		pinMode(id, OUTPUT);
	}

	inline uint8_t DigitalRead() const {
		return digitalRead(id);
	}
	inline void DigitalWrite(uint8_t value) const {
		return digitalWrite(id, value);
	}
	// It's not a real analog write, but a Pulse Width Modulation...
	inline void AnalogWrite(uint8_t val) const {
		analogWrite(id, val);
	}

	inline uint16_t AnalogRead() const {
		if (!digital)
			return analogRead(id - 14);
		return 0;
	}

	inline uint8_t getId() const {
		return id;
	}

	~Pin() {
	}

	inline bool DirectRead() {
		return (((*(inputregister)) & (mask)) ? 1 : 0);
	}

	inline void DirectInputMode() {
		((*((inputregister) + 1)) &= ~(mask));
	}
	inline void DirectOutputMode() {
		((*((inputregister) + 1)) |= (mask));
	}
	inline void DirectWrite(bool value) {
		if (value)
			((*((inputregister) + 2)) |= (mask));
		else
			((*((inputregister) + 2)) &= ~(mask));
	}

protected:
	uint8_t id;
	bool digital;
	// Move to methods.
	volatile uint8_t *inputregister;
	uint8_t mask;
};
}

#endif /* PIN_H_ */
