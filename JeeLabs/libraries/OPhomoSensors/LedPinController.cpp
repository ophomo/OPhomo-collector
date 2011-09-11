/*
 * LedPinController.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "LedPinController.h"

namespace OPhomo {

LedPinController::LedPinController(Pin* inPin) {
	pin = inPin;
}

void LedPinController::On() {
	pin->OutputMode();
	pin->DigitalWrite(0);
}

void LedPinController::Off() {
	pin->OutputMode();
	pin->DigitalWrite(1);
}

LedPinController::~LedPinController() {
}

}
