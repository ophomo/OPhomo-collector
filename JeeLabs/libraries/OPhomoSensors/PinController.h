/*
 * PinController.h
 *
 *  Created on: Jan 23, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef PINCONTROLLER_H_
#define PINCONTROLLER_H_
#include "Pin.h"

namespace OPhomo {

class PinController {
public:
	PinController(Pin* inPin);
	virtual ~PinController();


protected:
	Pin* pin;

};

}

#endif /* PINCONTROLLER_H_ */
