/*
 * JeePort
 *
 *  Created on: Jan 23, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */
#include "JeePort.h"


namespace OPhomo {

JeePort::JeePort(uint8_t inId, Pin* irq): id(inId), analogPin(inId-1,false), digitalPin(inId+3,true) {
	irqPin = irq;
}

JeePort::~JeePort() {
	// Cleanup the controllers.
}

uint8_t JeePort::getId() const {
	return id;
}


// TODO Auto-generated destructor stub
}
