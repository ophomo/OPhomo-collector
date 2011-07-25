/*
 * JeeNode.h
 *
 *  Created on: Jan 23, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef JEENODE_H_
#define JEENODE_H_

#include "JeePort.h"
#include "RF12Module.h"
#include "AnalogPin.h"

namespace OPhomo {

class JeeNode {
public:

	JeeNode();

	/**
	 * This will configure a JeeNode, based on an incoming OConfirationMessage
	 */
//	bool Configure(uint8_t* message, uint16_t length);

	inline JeePort& getPort1() {
		return port1;
	}

	inline JeePort& getPort2() {
		return port2;
	}

	inline JeePort& getPort3() {
		return port3;
	}

	inline JeePort& getPort4() {
		return port4;
	}

	inline RF12Module& getRF12() {
		return rf12;
	}

	virtual ~JeeNode();
protected:
	/* The IRQ pin is shared on all ports. Therefore, we put it on the JeeNode instead
	 * of on the port.
	 */
	AnalogPin irqPin;

	JeePort port1;
	JeePort port2;
	JeePort port3;
	JeePort port4;

	// RF12 module
	RF12Module rf12;
};

}

#endif /* JEENODE_H_ */
