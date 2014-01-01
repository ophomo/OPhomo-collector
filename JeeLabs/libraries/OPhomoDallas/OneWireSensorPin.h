/*
 * OneWireSensorChainStub.h
 *
 *  Created on: 26 Aug 2011
 *      Author: OPhomo
 */

#ifndef ONEWIRESENSORCHAINSTUB_H_
#define ONEWIRESENSORCHAINSTUB_H_

#include "Pin.h"
namespace OPhomo {
class OneWireSensorPin {
public:
	OneWireSensorPin(Pin* inPin);

	uint8_t Reset();

	void WriteBit(uint8_t v);

	uint8_t ReadBit(void);

	void Write(uint8_t v, uint8_t power = 1);

	uint8_t Read();

	void Skip();

	void Depower();

	~OneWireSensorPin();

protected:
	Pin* pin;
};
}
#endif /* ONEWIRESENSORCHAINSTUB_H_ */
