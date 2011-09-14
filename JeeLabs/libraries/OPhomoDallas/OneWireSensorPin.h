/*
 * OneWireSensorChainStub.h
 *
 *  Created on: 26 Aug 2011
 *      Author: OPhomo
 */

#ifndef ONEWIRESENSORCHAINSTUB_H_
#define ONEWIRESENSORCHAINSTUB_H_


#include "OneWireSensorChainInterface.h"
#include "Pin.h"
namespace OPhomo {
class OneWireSensorPin: public OneWireSensorChainInterface {
public:
	OneWireSensorPin(Pin* inPin);

	uint8_t Reset();

	void WriteBit(uint8_t v);

	uint8_t ReadBit(void);

	void Write(uint8_t v, uint8_t power = 0);

	uint8_t Read();

	void Skip();

	void Depower();

	virtual OneWireSensor* operator[] (uint8_t) ;

	virtual ~OneWireSensorPin();

	virtual uint8_t InitReadSensor();

	virtual void ReadSensor(MeasurementHandler* handler) {
		return;
	}

protected:
	Pin* pin;
};
}
#endif /* ONEWIRESENSORCHAINSTUB_H_ */
