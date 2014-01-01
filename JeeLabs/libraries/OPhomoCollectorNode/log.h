/*
 * log.h
 * This file supports logging, ... on the JeeNodes.
 * Because collector nodes and sensor nodes are completely different,
 * we use specific defines and methods to log messages.
 * We have currently one restriction: we limit the message length to 50 bytes,
 * so we can always transmit it in one message over the RF12 link, if needed.
 *
 *
 * UPDATE:
 * Later on, I decided to put all the code in the Collector and SensorNode separatly, because of
 * the many differences.
 *
 *  Created on: 7 Aug 2011
 *      Author: OPhomo
 */

#ifndef LOG_H_
#define LOG_H_

#define UNDEFINED_TYPE 0
#define ERROR_TYPE 1
#define WARNING_TYPE 2
#define INFO_TYPE 3
#define DEBUG_TYPE 4
#define STATUS_TYPE 5
#define RESULT_TYPE 6

#include "Logger.h"
#if 1
extern OPhomo::Logger* logger;
#define ERROR(...) logger->SetType(ERROR_TYPE); \
	logger->Append(__VA_ARGS__);
#define ERRORLN(...) ERROR(__VA_ARGS__)\
		logger->Done();
#define WARNING(...) logger->SetType(WARNING_TYPE); \
	logger->Append(__VA_ARGS__);
#define WARNINGLN(...) WARNING(__VA_ARGS__)\
		logger->Done();
#define INFO(...) logger->SetType(INFO_TYPE); \
	logger->Append(__VA_ARGS__);
#define INFOLN(...) INFO(__VA_ARGS__)\
		logger->Done();
#define DEBUG(...) logger->SetType(DEBUG_TYPE); \
	logger->Append(__VA_ARGS__);
#define DEBUGLN(...) DEBUG(__VA_ARGS__)\
		logger->Done();
#else
#define ERROR(...)
#define ERRORLN(...)
#define WARNING(...)
#define WARNINGLN(...)
#define INFO(...)
#define INFOLN(...)
#define DEBUG(...)
#define DEBUGLN(...)
#endif

#endif /* LOG_H_ */
