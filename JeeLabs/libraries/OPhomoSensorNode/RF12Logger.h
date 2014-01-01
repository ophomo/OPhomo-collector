/*
 * RF12Logger.h
 *
 *  Created on: 22 Aug 2011
 *      Author: OPhomo
 */
#if NEEDRF12_LOGGER
#ifndef RF12LOGGER_H_
#define RF12LOGGER_H_
#include "Logger.h"

namespace OPhomo {

class RF12Logger : public Logger {
public:
	virtual void Append(const int);

	virtual void Append(const double);

	virtual void Append(const char*);

	virtual void Append(byte*, byte);

	virtual void Done();

	static RF12Logger* getInstance() {
		if ( instance )
			return instance;
		else {
			instance = new RF12Logger();
			return instance;
		}
	}
protected:
	RF12Logger();

	virtual ~RF12Logger();

	virtual void Begin();

	static RF12Logger* instance;

};

}

#endif /* RF12LOGGER_H_ */
#endif
