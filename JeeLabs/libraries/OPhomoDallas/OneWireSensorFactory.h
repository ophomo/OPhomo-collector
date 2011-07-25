/*
 * OneWireSensorFactory.h
 *
 * This class will create a sensor for the OneWire sensor found.
 * Currently, we support different temperature sensors, but additional sensors could be added easily.
 *
 * This class is more then just a factory. It keeps its created sensors stored too, but that is just
 * a design decision.
 *
 *  Created on: Feb 6, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef ONEWIRESENSORFACTORY_H_
#define ONEWIRESENSORFACTORY_H_
#include "OneWireSensor.h"
#include "wiring.h"

#define _1WIRE_WAIT_9_BIT  0x1F //  9 bit
#define _1WIRE_WAIT_10_BIT 0x3F // 10 bit
#define _1WIRE_WAIT_11_BIT 0x5F // 11 bit
#define _1WIRE_WAIT_12_BIT 0x7F // 12 bit
// This defines the maximum number of sensors we support per factory. This is low by default, but if you want, just increase it...
#define MAXDALLASSENSORS 8

namespace OPhomo {

class OneWireSensorFactory {
public:
	OneWireSensorFactory();

	/**
	 * Method which will be called by the OneWire
	 * @param pinController The OneWirePinController which has found this device.
	 * @param address Address if the sensor found.
	 * @return 0 if failed, 1 if successful
	 */
	uint8_t Create(OneWirePinController* pinController, DeviceAddress& address);

	/**
	 * This retrieves the maximum conversion delay for the sensors collected by this factory.
	 */
	uint8_t GetMaxConversionDelay();

	static void WaitForConversion(uint8_t conversionDelay) {
		switch (conversionDelay) {
		case _1WIRE_WAIT_9_BIT:
			delay(94);
			break;
		case _1WIRE_WAIT_10_BIT:
			delay(188);
			break;
		case _1WIRE_WAIT_11_BIT:
			delay(375);
			break;
		case _1WIRE_WAIT_12_BIT:
		default:
			delay(750);
			break;
		}
	}

	/**
	 * Removes all the current installed sensors.
	 */
	void ClearSensors();

	virtual ~OneWireSensorFactory();

protected:
	OneWireSensor* sensors[MAXDALLASSENSORS];
	uint8_t position;
};

}

#endif /* ONEWIRESENSORFACTORY_H_ */
