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

namespace OPhomo {
class Pin {
public:
	Pin(uint8_t id) {
		this->id = id;
	}

    inline virtual void InputMode() const =0;
    inline virtual void OutputMode() const =0;
    inline virtual uint8_t DigitalRead() const =0;
    inline virtual void DigitalWrite(uint8_t value) const =0;
    inline uint8_t getId() const {
    	return id;
    }



	virtual ~Pin() {
	}

protected:
	uint8_t id;
};
}




#endif /* PIN_H_ */
