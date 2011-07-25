/*
 * JeeLink.h
 *
 *  Created on: Feb 12, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef JEELINK_H_
#define JEELINK_H_
#include "RF12Module.h"
#include "DigitalPin.h"
#include "LedPinController.h"

namespace OPhomo {

class JeeLink {
public:
	JeeLink();

	virtual ~JeeLink();

protected:
	// Activity Led
	DigitalPin activityPin;
	LedPinController activityLed;

	// RF12 module
	RF12Module rf12;

};

}

#endif /* JEELINK_H_ */
