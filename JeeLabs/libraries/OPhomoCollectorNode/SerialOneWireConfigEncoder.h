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

	void Handle(byte* buffer, byte length);

	virtual ~SerialOneWireConfigEncoder();
};
}

#endif /* SERIALONEWIRECONFIGENCODER_H_ */
