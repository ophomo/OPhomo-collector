/*
 * JeePort.h
 *
 *  Created on: Jan 23, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef JEEPORT_H_
#define JEEPORT_H_
#include <stdint.h>
#include "Pin.h"
#include "AnalogPin.h"
#include "DigitalPin.h"
namespace OPhomo {

enum PinType {
	DIGITAL = 0, ANALOG
};

class JeePort {
public:
	JeePort(uint8_t inId, AnalogPin* irq);

	virtual ~JeePort();

	// The id is not part of the configuration. We just need it to assign the configuration to the correct pin.
	uint8_t getId() const;

	inline AnalogPin& getAnalogPin()
    {
        return analogPin;
    }

    inline DigitalPin& getDigitalPin()
    {
        return digitalPin;
    }

private:
	uint8_t id;
	AnalogPin analogPin;
	DigitalPin digitalPin;
	AnalogPin* irqPin;
};

}

#endif /* JEEPORT_H_ */
