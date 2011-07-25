/*
 * RF12Module.cpp
 *
 *  Created on: Jan 26, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "RF12Module.h"
#include <string.h>
#include <util/crc16.h>
#include <avr/eeprom.h>
#include <HardwareSerial.h>

#define COLLECT 0x20 // collect mode, i.e. pass incoming without sending acks
namespace OPhomo {

int pow(int a, unsigned int b) {
	switch (b) {
	case 0:
		return 1;
	case 1:
		return a;
	default:
		return (a * pow(a, b - 1));
	}
}

#define ADD_CHAR(msg,c) \
	len = strlen(msg); \
	msg[len] = c;

#define ADD_INT(msg,i) \
		pos = 0; \
		len = strlen(msg); \
		remainder = i; \
		while ( remainder > 10 ) { \
			pos++; \
			remainder /= 10; \
		} \
		msg[len++] = remainder; \
		while (pos) \
			msg[len++] = i / pow(10,pos--);

RF12Module::RF12Module() {
}

void RF12Module::init() {
	if (rf12_config()) {
		nodeId = eeprom_read_byte(RF12_EEPROM_ADDR);
		group = eeprom_read_byte(RF12_EEPROM_ADDR + 1);
	} else {
		nodeId = 0x41; // node A1 @ 433 MHz
		group = 0xD4;
		SaveConfig();
	}
	// Is this required ?
	//	rf12_easyInit(5);
}

void RF12Module::SetMinimumSendInterval(int value) {
	rf12_easyInit(value);
}

bool RF12Module::SaveConfig() {
	// Variables used by the macros...
	byte pos, len;
	int remainder;
	memset(msg, 0, sizeof msg);
	strcpy(msg, " ");

	byte id = nodeId & 0x1F;
	ADD_CHAR(msg, '@' + id);
	strcat(msg, " i");
	ADD_INT(msg, id);
	if (nodeId & COLLECT)
		ADD_CHAR(msg, '*');

	strcat(msg, " g");
	ADD_INT(msg, group);

	strcat(msg, " @ ");
	static word bands[4] = { 315, 433, 868, 915 };
	word band = nodeId >> 6;
	ADD_INT(msg, bands[band]);
	strcat(msg, " MHz ");

	crc = ~0;
	for (byte i = 0; i < sizeof(*this) - 2; ++i)
		crc = _crc16_update(crc, ((byte*) this)[i]);

	// save to EEPROM
	for (byte i = 0; i < sizeof(*this); ++i) {
		byte b = ((byte*) this)[i];
		eeprom_write_byte(RF12_EEPROM_ADDR + i, b);
	}
	if (!rf12_config())
		return false;
	return true;
}

byte RF12Module::getGroupId() const {
	return group;
}

byte RF12Module::getNodeId() const {
	return nodeId & 0x1F;
}

byte RF12Module::getBand() const {
	return (nodeId >> 6);
}

void RF12Module::setGroupId(byte group) {
	this->group = group;
	rf12_initialize(nodeId, nodeId >> 6, group);
}

void RF12Module::setNodeId(byte nodeId) {
	this->nodeId &= (nodeId & 0x1F);
	rf12_initialize(nodeId, nodeId >> 6, group);
}

void RF12Module::setBand(byte band) {
	this->nodeId &= 0x1F;
	this->nodeId |= (band << 6);
	rf12_initialize(nodeId, band, group);
}

byte RF12Module::TryReceive(byte *&message) {
	if (rf12_recvDone()) {
		if (rf12_crc != 0) {
			return false;
		}
		// This is a nice idea, but this will ruin our buffer...
		/*		if (RF12_WANTS_ACK && (nodeId & COLLECT) == 0) {
		 rf12_sendStart(RF12_ACK_REPLY, 0, 0);
		 } */
		// We return everything...
		message = (uint8_t*) rf12_buf;
		return rf12_len;
	} else {
		return 0;
	}
}

bool RF12Module::Send(byte destination, byte* message, uint8_t sendLen,
		bool needAck) {
	if (rf12_canSend()) {
		byte header = needAck ? RF12_HDR_ACK : 0;
		if (destination)
			header |= RF12_HDR_DST | destination;
		rf12_sendStart(header, message, sendLen);
		rf12_sendWait(1);
		return true;
	} else {
		// What must we do...
		return false;
	}
}

RF12Module::~RF12Module() {
}

}
