/*
 * Logger.h
 *
 *  Created on: 16 Aug 2011
 *      Author: OPhomo
 *  Interface defining the signature of the OPhomo logger.
 *  We need to define the interface here, because even the sensors require logging for debugging, ... purposes.
 */

#ifndef LOGGER_H_
#define LOGGER_H_
#include "wiring.h"

namespace OPhomo {

class Logger {
public:
	Logger() {
		type = 0;
	};

	inline void SetType(byte intype ) {
		if (type != intype ) {
			// The programmer is lazy : we have an open log, but need to close it so we can start a fresh one...
			this->Done();
			type = intype;
			this->Begin();
		}
	}

	virtual void Append(const int) = 0;

	virtual void Append(const double) = 0;

	virtual void Append(const char* ) = 0;

	virtual void Append(byte*,byte) = 0;

	virtual void Done() {};

	virtual ~Logger() {};

protected:
	byte type;

	virtual void Begin() {};
};

}

#endif /* LOGGER_H_ */
