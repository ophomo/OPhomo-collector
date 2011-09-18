/*
 * EncoderTypeDecorator.h
 *
 *  Created on: 15 Aug 2011
 *      Author: OPhomo
 */

#ifndef ENCODERTYPEDECORATOR_H_
#define ENCODERTYPEDECORATOR_H_

#include "EncoderDecorator.h"

namespace TLV {

class EncoderTypeDecorator: public TLV::EncoderDecorator {
public:
	enum Type {
		UNKNOWN = 0,
		BYTE,
		INT,
		DOUBLE,
		CHAR,
		CHARP,
		BYTEP
	};

	EncoderTypeDecorator(EncoderInterface *c);

	byte Encode(byte* to, int value );

	byte Encode(byte* to, char* value);

	byte Encode(byte* to, byte* value, byte length );

	byte Encode(byte* to, double value);

	virtual ~EncoderTypeDecorator();
};

}

#endif /* ENCODERTYPEDECORATOR_H_ */
