/*
 * RF12Logger.cpp
 *
 *  Created on: 22 Aug 2011
 *      Author: OPhomo
 */


#include "RF12Logger.h"
#if NEEDRF12_LOGGER
namespace OPhomo {

RF12Logger* RF12Logger::instance = NULL;

RF12Logger::RF12Logger() {
	// TODO Auto-generated constructor stub

}

RF12Logger::~RF12Logger() {
	// TODO Auto-generated destructor stub
}

void RF12Logger::Append(const int) {}

void RF12Logger::Append(const double) {}

void RF12Logger::Append(const char*) {}

void RF12Logger::Append(byte*, byte) {};

void RF12Logger::Done() {};

void RF12Logger::Begin() {};

}

OPhomo::Logger* logger = OPhomo::RF12Logger::getInstance();
#endif
