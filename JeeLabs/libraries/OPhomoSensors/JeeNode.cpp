/*
 * JeeNode.cpp
 *
 *  Created on: Jan 23, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "JeeNode.h"


namespace OPhomo {
/*
enum {
	rf12Mod = 0,
	irqController,
	port1Config,
	port2Config,
	port3Config,
	port4Config
};

struct genConfigHeader {
	uint8_t type :3;
	uint8_t more :5;
};
*/
JeeNode::JeeNode() : irqPin(3, false), port1(1, &irqPin), port2(2, &irqPin), port3(3, &irqPin), port4(4, &irqPin)  {
/*	rf12.setBand(RF12_868MHZ);
	rf12.setGroupId(212);
	rf12.setNodeId(7);
	rf12.SaveConfig();*/
}

/* bool JeeNode::Configure(uint8_t* message, uint16_t length) {
	uint16_t pos = 0;
	genConfigHeader* header;
	while (pos < length) {
		// Apply the genConfigHeader
		header = (genConfigHeader*) (message + pos);
		switch (header->type) {
		case rf12Mod: {
			// This is a variable length item
			// TODO implement this.
			rf12.Configure( message + pos, header->more );
			pos += header->more;
		}
			break;
		case irqController: {
			// This is a variable length one.
			pos += header->more;

		}
			break;
		case port1Config: {
			// This is a variable length one.
			port1.Configure(message + pos + 1, header->more);
			pos += header->more;

		}
			break;
		case port2Config: {
			// This is a variable length one.
			port2.Configure(message + pos + 1, header->more);
			pos += header->more;
		}
			break;
		case port3Config: {
			// This is a variable length one.
			port3.Configure(message + pos + 1, header->more);
			pos += header->more;
		}
			break;
		case port4Config: {
			// This is a variable length one.
			port4.Configure(message + pos + 1, header->more);
			pos += header->more;
		}
			break;
		default: {
			return false;
		}

		}

	}
	return true;

}
*/

JeeNode::~JeeNode() {
}

}
