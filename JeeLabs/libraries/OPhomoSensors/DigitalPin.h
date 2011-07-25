/*
 * DigitalPin.h
 *
 *  Created on: Jan 26, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef DIGITALPIN_H_
#define DIGITALPIN_H_

#include "Pin.h"
#include "wiring.h"

namespace OPhomo {
class DigitalPin: public OPhomo::Pin {
public:
	DigitalPin(uint8_t id);

	inline void InputMode() const {
		pinMode(id,INPUT);
	}
	inline void OutputMode() const {
		pinMode(id,OUTPUT);
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

	inline uint32_t Pulse(uint8_t state, uint32_t timeout = 1000000L) const {
		return pulseIn(id, state, timeout);
	}


	virtual ~DigitalPin();
};
}

#endif /* DIGITALPIN_H_ */
