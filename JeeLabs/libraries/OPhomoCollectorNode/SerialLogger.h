/*
 * SerialLogger.h
 *
 *  Created on: 17 Aug 2011
 *      Author: OPhomo
 */

#ifndef SERIALLOGGER_H_
#define SERIALLOGGER_H_

#include "Logger.h"

namespace OPhomo {

class SerialLogger: public OPhomo::Logger {
public:
	SerialLogger();

	virtual ~SerialLogger();

	virtual void Append(const int);

	virtual void Append(const double);

	virtual void Append(const char*);

	virtual void Append(byte*, byte);

	virtual void Done();

	static SerialLogger* getInstance() {
		if ( instance )
			return instance;
		else {
			instance = new SerialLogger();
			return instance;
		}
	}

protected:
	virtual void Begin();

	static SerialLogger* instance;
};

}

extern OPhomo::Logger* logger;

#endif /* SERIALLOGGER_H_ */
