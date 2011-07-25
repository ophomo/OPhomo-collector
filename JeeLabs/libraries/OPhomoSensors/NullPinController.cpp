/*
 * NullPinController.cpp
 *
 *  Created on: Jan 24, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "NullPinController.h"
namespace OPhomo {
NullPinController::NullPinController(Pin* pin): PinController(pin) {
}

NullPinController::~NullPinController() {
}
}
