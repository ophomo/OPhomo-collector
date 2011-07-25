/*
 * AnalogPin.h
 *
 *  Created on: Jan 26, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef ANALOGPIN_H_
#define ANALOGPIN_H_

#include "Pin.h"
#include "wiring.h"

#include "HardwareSerial.h"

namespace OPhomo {
class AnalogPin: public OPhomo::Pin {
public:
	AnalogPin(uint8_t id);

	inline void InputMode() const {
		pinMode(id + 14, INPUT);
	}
	inline void OutputMode() const {
		pinMode(id + 14, OUTPUT);
	}
	inline uint16_t AnalogRead() const {
		return analogRead(id);
	}
	inline uint8_t DigitalRead() const {
		return digitalRead(id + 14);
	}
	inline void DigitalWrite(uint8_t value) const {
		digitalWrite(id + 14, value);
	}

	virtual ~AnalogPin();
};

}

#endif /* ANALOGPIN_H_ */
