/*
 * EncoderLenghtDecorator.cpp
 *
 *  Created on: 15 Aug 2011
 *      Author: OPhomo
 */

#include "EncoderLengthDecorator.h"

namespace TLV {

EncoderLengthDecorator::EncoderLengthDecorator(EncoderInterface* c) : EncoderDecorator(c) {
}

byte EncoderLengthDecorator::Encode(byte* to, int value ) {
	*to = inner->Encode(to+1,value);
	return (*to) + 1;
}

byte EncoderLengthDecorator::Encode(byte* to, char* value) {
	*to = inner->Encode(to+1,value);
	return (*to) + 1;
}

byte EncoderLengthDecorator::Encode(byte* to, byte* value, byte length ) {
	*to = inner->Encode(to+1,value, length);
	return (*to) + 1;
}

byte EncoderLengthDecorator::Encode(byte* to, double value) {
	*to = inner->Encode(to+1,value);
	return (*to) + 1;
}

byte EncoderLengthDecorator::Encode(byte* to, TLVEncodableObject& value) {
	*to = inner->Encode(to+1,value);
	return (*to) + 1;
}



EncoderLengthDecorator::~EncoderLengthDecorator() {
}

}
