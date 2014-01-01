#include "OPhomoProtocolHeader.h"

namespace OPhomo {

/**
 * This is how we structure our ID in a One Wire message.
 * 2 bits for the port
 * 1 bit for the pin
 * 5 bits for the real value
 */
struct OneWireID {
	byte value : 5;
	byte pin   : 1;
	byte port  : 2;
};

struct OneWireConfigReply {
	OneWireConfigReply() :
		type(ONEWIRE_SENSOR_CONFIG_TYPE),
				length(sizeof(OneWireConfigReply) - 2) {
	}

	byte type;
	byte length;
	byte state;
	OneWireID id;
	byte port_port :7;
	byte port_pin :1;
	DeviceAddress address;

};


}


