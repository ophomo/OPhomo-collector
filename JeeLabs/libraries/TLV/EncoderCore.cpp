/*
 * EncoderCore.cpp
 *
 *  Created on: 13 Aug 2011
 *      Author: OPhomo
 */

#include "EncoderCore.h"
#include "string.h"

namespace TLV {

EncoderCore::EncoderCore() {
}

byte EncoderCore::Encode(byte* to, int value ) {
	memcpy(to, &value, sizeof(int));
	return sizeof(int);
}

byte EncoderCore::Encode(byte* to, char* value) {
	byte pos = 0;
	for (pos = 0; pos <= 255; pos++ ) {
		if ( value[pos] == '\0')
			break;
	}
	memcpy( to, value, pos );
	return pos;
}

byte EncoderCore::Encode(byte* to, byte* value, byte length ) {
	memcpy( to, value, length );
	return length;
}

byte EncoderCore::Encode(byte* to, double value) {
	memcpy( to, &value, sizeof(double) );
	return sizeof(double);
}


EncoderCore::~EncoderCore() {
}

}
