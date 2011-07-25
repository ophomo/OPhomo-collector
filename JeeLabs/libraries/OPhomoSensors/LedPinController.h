/*
 * LedPinController.h
 *
 *  Created on: Feb 12, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef LEDPINCONTROLLER_H_
#define LEDPINCONTROLLER_H_

#include "PinController.h"

namespace OPhomo {

class LedPinController: public OPhomo::PinController {
public:
	LedPinController(Pin* inPin);

	void On();


	void Off();


	virtual ~LedPinController();
};

}

#endif /* LEDPINCONTROLLER_H_ */
