/*
 * EncoderDecorator.h
 *
 *  Created on: 14 Aug 2011
 *      Author: OPhomo
 */

#ifndef ENCODERDECORATOR_H_
#define ENCODERDECORATOR_H_
#include "EncoderInterface.h"

namespace TLV {

class EncoderDecorator: public EncoderInterface {
protected:
	EncoderInterface *inner;

public:
	EncoderDecorator(EncoderInterface *c) : EncoderInterface() {
		inner = c;
	}
	~EncoderDecorator() {
		delete inner;
	}
};

}

#endif /* ENCODERDECORATOR_H_ */
