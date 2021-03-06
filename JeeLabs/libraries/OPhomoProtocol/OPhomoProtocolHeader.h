/*
 * OPhomoProtocolHeader.h
 *
 *  Created on: Feb 16, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef OPHOMOPROTOCOLHEADER_H_
#define OPHOMOPROTOCOLHEADER_H_
#include "Arduino.h"

enum ProtocolStatus {
	CONFIG_SOLICIT = 0, CONFIG_ACCEPT, OPERATIONAL, UPDATE_SOLICIT
};

#define	 CONFIG_SOLICIT_TYPE 0
#define	 CONFIG_ADVERTISE_TYPE 1
#define	 CONFIG_REJECT_TYPE 2
#define	 CONFIG_ACCEPT_TYPE 3
#define CONFIG_ACK_TYPE 4
#define REPORT_TYPE 5

#define CONFIG_SOLICIT_LENGTH sizeof(OPhomoProtocolHeader)

struct OPhomoProtocolHeader {
	byte MessageType :3;
	byte SourceNode :5;
};

// Node configs start with 0100xxxx
#define OPHOMOPROTOCOL_CONFIG_TYPE  64
#define RF12_CONFIG_TYPE            65
// Sensor type start with 0101xxxx
#define ONEWIRE_SENSOR_CONFIG_TYPE   80
#define ROOMNODE_SENSOR_CONFIG_TYPE 81

#endif /* OPHOMOPROTOCOLHEADER_H_ */
