/*
 * SerialChannel.h
 *
 *  Created on: Jan 11, 2011
 *      Author: decock
 */

#ifndef SERIALCHANNEL_H_
#define SERIALCHANNEL_H_

#include <string>

class SerialChannel {
public:
	SerialChannel();

	virtual ~SerialChannel();

	/**
	 * Gets the device string.
	 * @return Name of the serial device. e.g. /dev/ttyUSB0
	 */
    std::string getDevice() const;

    /**
     * This set the device string of the serial port.
     * @input Device name e.g. /dev/ttyUSB0
     */
    void setDevice(std::string device);

    /**
     * This will connect to the serial channel, configure the baudrate, .... like expected for a JeeNode.
     */
    bool Connect();

protected:
	std::string device;
	// File descriptor to the serial port.
	int fd;
};

#endif /* SERIALCHANNEL_H_ */
