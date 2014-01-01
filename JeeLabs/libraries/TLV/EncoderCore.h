/*
 * EncoderCore.h
 *
 *  Created on: 13 Aug 2011
 *      Author: OPhomo
 */

#ifndef ENCODERCORE_H_
#define ENCODERCORE_H_

#include "EncoderInterface.h"

namespace TLV {

class EncoderCore: public TLV::EncoderInterface {
public:
	EncoderCore();

	byte Encode(byte* to, int value ) ;

	byte Encode(byte* to, char* value);

	byte Encode(byte* to, byte* value, byte length );

	byte Encode(byte* to, double value);

	byte Encode(byte* to, TLVEncodableObject& object);


	virtual ~EncoderCore();
};

}

#endif /* ENCODERCORE_H_ */
