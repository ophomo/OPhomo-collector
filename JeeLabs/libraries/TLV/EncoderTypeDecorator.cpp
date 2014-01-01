/*
 * EncoderTypeDecorator.cpp
 *
 *  Created on: 15 Aug 2011
 *      Author: OPhomo
 */

#include "EncoderTypeDecorator.h"

namespace TLV {

EncoderTypeDecorator::EncoderTypeDecorator(EncoderInterface *c) :
	EncoderDecorator(c) {
}

byte EncoderTypeDecorator::Encode(byte* to, int value) {
	*to = INT;
	return inner->Encode(to + 1, value) + 1;
}

byte EncoderTypeDecorator::Encode(byte* to, char* value) {
	*to = CHARP;
	return inner->Encode(to + 1, value) + 1;
}

byte EncoderTypeDecorator::Encode(byte* to, byte* value, byte length) {
	*to = BYTEP;
	return inner->Encode(to + 1, value, length) + 1;

}

byte EncoderTypeDecorator::Encode(byte* to, double value) {
	*to = DOUBLE;
	return inner->Encode(to + 1, value) + 1;
}

byte EncoderTypeDecorator::Encode(byte* to,  TLVEncodableObject& object) {
	*to = object.getType();
	return inner->Encode(to + 1, object) + 1;
}


EncoderTypeDecorator::~EncoderTypeDecorator() {
}

}
