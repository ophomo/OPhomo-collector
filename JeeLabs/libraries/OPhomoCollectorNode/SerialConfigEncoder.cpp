/*
 * SerialConfigEncoder.cpp
 *
 *  Created on: Feb 26, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "SerialConfigEncoder.h"

OPhomo::RF12Concatenator OPhomo::SerialConfigEncoder::transmitter;
byte OPhomo::SerialConfigEncoder::encodedMessage[RF12_MAXDATA];
byte OPhomo::SerialConfigEncoder::messageLength = 0;
