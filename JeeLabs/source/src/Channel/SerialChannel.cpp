/*
 * SerialChannel.cpp
 *
 *  Created on: Jan 11, 2011
 *      Author: decock
 */

#include "SerialChannel.h"
#include <stdio.h>   /* Standard input/output definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdexcept>

SerialChannel::SerialChannel() {
	// TODO Auto-generated constructor stub
	fd = 0;
}

SerialChannel::~SerialChannel() {
	// TODO Auto-generated destructor stub
	if (fd)
		close (fd);
}

std::string SerialChannel::getDevice() const {
	return device;
}

void SerialChannel::setDevice(std::string device) {
	this->device = device;
}

bool SerialChannel::Connect() {
	fd = open(this->device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		/*
		 * Could not open the port.
		 */
		throw std::runtime_error("Unable to open serial port " + device + ".");
	} else
		// This sets the port in blocking mode. I think we are better with blocking mode in this case.
		fcntl(fd, F_SETFL, 0);
	// Time for the options
	struct termios options;

	/*
	 * Get the current options for the port...
	 */

	tcgetattr(fd, &options);

	/*
	 * Set the baud rates to 57600...
	 */

	cfsetispeed(&options, B57600);
	cfsetospeed(&options, B57600);

	/*
	 * Enable the receiver and set local mode...
	 */
	options.c_cflag |= (CLOCAL | CREAD);

	// Setting no parity.
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	// No hardware flow control
//	options.c_cflag &= ~CNEW_RTSCTS;
	// No software flow control
	options.c_iflag &= ~(IXON | IXOFF | IXANY);
	// We will use it line based.
	options.c_lflag |= (ICANON );

	/*
	 * Set the new options for the port...
	 */
	if ( tcsetattr(fd, TCSANOW, &options) != 0 ) {
		throw std::runtime_error("Failed to configure baudrate on serial interface.");
	}

}

