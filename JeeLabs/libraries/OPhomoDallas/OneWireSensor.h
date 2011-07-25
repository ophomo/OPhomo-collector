/*
 * OneWireSensor.h
 *
 *  Created on: Feb 6, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef ONEWIRESENSOR_H_
#define ONEWIRESENSOR_H_

#include "OneWirePinController.h"

namespace OPhomo {

class OneWireSensor {
public:
	OneWireSensor();

	virtual bool isParasite() = 0;

	virtual uint8_t GetConversionDelay() = 0;

	virtual void Initialize(OneWirePinController* pinController,
				DeviceAddress& deviceAddress) = 0;

	uint8_t* GetDeviceAddress() {
		return deviceAddress;
	}

	virtual ~OneWireSensor();

protected:
	OneWirePinController* pinController;
	DeviceAddress deviceAddress;
};

}

#endif /* ONEWIRESENSOR_H_ */
