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

#include "OneWireSensorChainInterface.h"
namespace OPhomo {

typedef uint8_t DeviceAddress[8];

class OneWireSensor: public OneWireSensorChainInterface {
public:
	OneWireSensor(OneWireSensorChainInterface* inWrappee, DeviceAddress& deviceAddress);

	// The low level methods, implemented by the OneWirePin.
	virtual uint8_t Reset() {
		return wrappee->Reset();
	}

	virtual void WriteBit(uint8_t v) {
		wrappee->WriteBit(v);
	}

	virtual uint8_t ReadBit(void) {
		return wrappee->ReadBit();
	}

	virtual void Write(uint8_t v, uint8_t power = 0) {
		wrappee->Write(v, power);
	}

	virtual uint8_t Read() {
		return wrappee->Read();
	}

	virtual void Skip() {
		wrappee->Skip();
	}

	virtual void Depower() {
		wrappee->Depower();
	}


	virtual uint8_t InitReadSensor();


	virtual bool isParasite() = 0;



	uint8_t* GetDeviceAddress() {
		return deviceAddress;
	}

	virtual ~OneWireSensor();

	virtual OneWireSensor* operator[] (uint8_t);

protected:
	void Select();

	virtual uint8_t GetConversionDelay() = 0;

	OneWireSensorChainInterface* wrappee;

	DeviceAddress deviceAddress;
};

}

#endif /* ONEWIRESENSOR_H_ */
