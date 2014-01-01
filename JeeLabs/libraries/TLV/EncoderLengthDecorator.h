/*
 * EncoderLenghtDecorator.h
 *
 *  Created on: 15 Aug 2011
 *      Author: OPhomo
 */

#ifndef ENCODERLENGHTDECORATOR_H_
#define ENCODERLENGHTDECORATOR_H_

#include "EncoderDecorator.h"

namespace TLV {

class EncoderLengthDecorator: public TLV::EncoderDecorator {
public:
	EncoderLengthDecorator(EncoderInterface* c);

	byte Encode(byte* to, int value );

	byte Encode(byte* to, char* value);

	byte Encode(byte* to, byte* value, byte length );

	byte Encode(byte* to, double value);

	byte Encode(byte* to, TLVEncodableObject& value);

	virtual ~EncoderLengthDecorator();
};

}

#endif /* ENCODERLENGHTDECORATOR_H_ */
