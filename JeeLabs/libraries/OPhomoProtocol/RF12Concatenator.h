/*
 * RF12Concatenator.h
 *
 *  Created on: 5 Jul 2011
 *      Author: decock
 */

#ifndef RF12CONCATENATOR_H_
#define RF12CONCATENATOR_H_
#include "RF12Module.h"

namespace OPhomo {

class RF12Concatenator {
public:
	RF12Concatenator(RF12Module* rf12);

	RF12Concatenator();

	void SetRF12Module(RF12Module* rf12) {
		rf12Module = rf12;
	}

	void SetDestinationNode(byte nodeId);

	/**
	 * This sets the type of the message.
	 */
	void SetMessageType(byte type);

	/**
	 * This will add a configuration part and send it if the message is full.
	 */
	void Send(byte*, byte length);

	/**
	 * This will send the last part of a configuration.
	 */
	void LastPartSend();

	virtual ~RF12Concatenator();
protected:
	void SendPartNow();

	RF12Module* rf12Module;
	byte buffer[RF12_MAXDATA];
    // position in the current buffer
	byte pos;

};

}

#endif /* RF12CONCATENATOR_H_ */
