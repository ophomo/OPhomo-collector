/*
 * SerialLogger.cpp
 *
 *  Created on: 17 Aug 2011
 *      Author: OPhomo
 */

#include "SerialLogger.h"
#include "HardwareSerial.h"
#include "log.h"

namespace OPhomo {

SerialLogger* SerialLogger::instance = NULL;

SerialLogger::SerialLogger() {
}

void SerialLogger::Append(const int value) {
	Serial.print(value);
}

void SerialLogger::Append(const double value) {
	Serial.print(value);
}

void SerialLogger::Append(const char* value) {
	Serial.print(value);
}

void SerialLogger::Append(byte*value , byte length) {
	Serial.write(value,length);
}

void SerialLogger::Begin() {
	switch (type) {
		case ERROR_TYPE: {
			Serial.print("ERR\t");
		}
		break;
		case WARNING_TYPE: {
			Serial.print("WAR\t");
		}
		break;
		case INFO_TYPE: {
			Serial.print("INF\t");
		}
		break;
		case DEBUG_TYPE: {
			Serial.print("DBG\t");
		}
		break;
		case STATUS_TYPE: {
			Serial.print("STA\t");
		}
		break;
		default:
			Serial.print("UNK\t");
			break;
	}
	//Serial.print();
	// @todo Add the node id...
}

void SerialLogger::Done() {
	Serial.println();
	type = 0;
}


SerialLogger::~SerialLogger() {
}

}

OPhomo::Logger* logger = OPhomo::SerialLogger::getInstance();
