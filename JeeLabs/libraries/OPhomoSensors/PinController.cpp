/*
 * PinController.cpp
 *
 *  Created on: Jan 23, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "PinController.h"

namespace OPhomo {

PinController::PinController(Pin* pin) {
	this->pin = pin;
}

PinController::~PinController() {
}

}
