/*
 * SerialOneWireConfigEncoder.h
 *
 *  Created on: Mar 8, 2011
 *      Author: decock
 */
#ifndef SERIALONEWIRECONFIGENCODER_H_
#define SERIALONEWIRECONFIGENCODER_H_

#include "SerialConfigEncoder.h"



#include "OPhomoProtocolHeader.h"
namespace OPhomo {
class SerialOneWireConfigEncoder: public OPhomo::SerialConfigEncoder {
public:
	SerialOneWireConfigEncoder();

	static const byte type[4];

	void EncodeSerial2Bin(byte* buffer, byte length);

	byte DecodeBin2Serial(byte* message, byte messageLength, char* serialBuffer, int* serialLength);

	virtual ~SerialOneWireConfigEncoder();

	byte getType();
};
}

#endif /* SERIALONEWIRECONFIGENCODER_H_ */
