/*
 * NullPinController.h
 *
 *  Created on: Jan 24, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef NULLPINCONTROLLER_H_
#define NULLPINCONTROLLER_H_

#include "PinController.h"
namespace OPhomo {

class NullPinController: public OPhomo::PinController {
public:
	NullPinController(Pin* pin);
	virtual ~NullPinController();
};

}
#endif /* NULLPINCONTROLLER_H_ */
