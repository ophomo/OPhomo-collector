/*
 * SerialHandler.h
 *
 *  Created on: Feb 21, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "RF12Concatenator.h"

#ifndef SERIALCONFIGENCODER_H_
#define SERIALCONFIGENCODER_H_

namespace OPhomo {
class SerialConfigEncoder {
public:
	SerialConfigEncoder() {
	}
	;

	/**
	 * Handle a line, transform it into a RF12 message.
	 */
	virtual void Handle(byte* buffer, byte length) = 0;

	virtual ~SerialConfigEncoder() {
	}

	static RF12Concatenator transmitter;

	// We use a static field to safe memory.
	static byte encodedMessage[RF12_MAXDATA];
	static byte messageLength;
protected:
	static int GetInt(byte* readBuffer, byte& position) {
		int result = 0;
		while (1) {
			if ('0' <= readBuffer[position] && readBuffer[position] <= '9')
				result = result * 10 + readBuffer[position++] - '0';
			else
				return result;
		}

	}

	static byte EncodeInt(int value, byte* writeBuffer, byte& position) {
		if (value >= 0) {
			// Let's make it small.
			byte size = 0;
			do {
				writeBuffer[position + size + 1] = (byte)(value >> (8 * size));
				size++;
			} while (value > ((1 << (8 * size)) - 1));
			writeBuffer[position] = size;
			position += 1 + size;
			return 1 + size;
		} else {
			// I currently don't know any other way then encode the whole integer.
			writeBuffer[position++] = sizeof(int);
			for (byte i = 0; i < sizeof(int); i++) {
				writeBuffer[position++] = (byte)(value >> (8 * i));
			}
			return 1 + sizeof(int);
		}
	}

};

}
#endif
