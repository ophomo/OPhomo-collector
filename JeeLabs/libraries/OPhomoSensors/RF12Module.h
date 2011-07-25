/*
 * RF12Module.h
 *
 *  Created on: Jan 26, 2011
 *      Author: dd@ophomo.org
 *
 * This is the OPhomo approach to RF12. Must things are taken from the RF12 demo.
 *
 * We currently support all basic things, but I would like to add encryption support too.
 *
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef RF12MODULE_H_
#define RF12MODULE_H_
#include <stdint.h>
#include <wiring.h>
#include "RF12.h"
namespace OPhomo {

class RF12Module {
public:
	RF12Module();

	/**
	 * This will initialize the RF12 module
	 */
	void init();

	/**
	 * This will store the config in the EPROM.
	 */
	bool SaveConfig();

	virtual ~RF12Module();

	/**
	 * This method will try to receive data. If possible, a pointer to the message will be set in the variable message.
	 */
	byte TryReceive(  byte* &message );

	/**
	 * This will send the message to destination node "Destination" and will
	 * request an ack if needAck is true.
	 */
	bool Send (byte destination, byte* message, uint8_t sendLen, bool needAck = false );

	/*
	 * This sets the minimum interval for sending ( in seconds )
	 */
	void SetMinimumSendInterval(int value);

	byte getBand() const;

	byte getGroupId() const;

	byte getNodeId() const;

	void setGroupId(byte group);

	void setNodeId(byte nodeId);

	void setBand(byte band);

protected:
	// This is what will be stored on the JeeNode/JeeLink
	byte nodeId;
	byte group;
	char msg[RF12_EEPROM_SIZE - 4];
	word crc;
};

}
#endif /* RF12MODULE_H_ */
