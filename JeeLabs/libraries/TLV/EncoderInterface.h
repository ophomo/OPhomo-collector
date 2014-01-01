/*
 * EncoderInterface.h
 *
 *  Created on: 13 Aug 2011
 *      Author: OPhomo
 */

#ifndef ENCODERINTERFACE_H_
#define ENCODERINTERFACE_H_

#include "TLVEncodableObject.h"

namespace TLV {

class EncoderInterface {
public:
	EncoderInterface();

	virtual byte Encode(byte* to, int value ) = 0;

	virtual byte Encode(byte* to, char* value) = 0;

	virtual byte Encode(byte* to, byte* value, byte length ) = 0;

	virtual byte Encode(byte* to, double value) = 0;

	virtual byte Encode(byte* to, TLVEncodableObject& value) = 0;

	virtual ~EncoderInterface();
};

}

#endif /* ENCODERINTERFACE_H_ */
