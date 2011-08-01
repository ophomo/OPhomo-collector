/*
 * SerialRF12ConfigEncoder.h
 *
 *  Created on: Feb 23, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#ifndef SERIALRF12CONFIGENCODER_H_
#define SERIALRF12CONFIGENCODER_H_
#include "SerialConfigEncoder.h"

namespace OPhomo {

class SerialRF12ConfigEncoder : public SerialConfigEncoder {
public:
	static const byte type[4];

	SerialRF12ConfigEncoder();

	void EncodeSerial2Bin(byte* buffer, byte length);

	byte getType();

	virtual ~SerialRF12ConfigEncoder();
protected:

};

}

#endif /* SERIALRF12CONFIGENCODER_H_ */
