/*
 * Plug.h
 *
 *  Created on: Feb 1, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef PLUG_H_
#define PLUG_H_
#include "JeePort.h"

namespace OPhomo {
class Plug {
public:
	Plug( OPhomo::JeePort* port ) {
		this->port = port;
	}



	virtual ~Plug();

protected:
	JeePort* port;
};
};
#endif /* PLUG_H_ */
