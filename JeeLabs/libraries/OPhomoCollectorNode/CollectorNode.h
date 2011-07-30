/*
 * CollectorNode.h
 *
 *  Created on: Feb 16, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef COLLECTORNODE_H_
#define COLLECTORNODE_H_

#include <JeeLink.h>

namespace OPhomo {

class CollectorNode: public OPhomo::JeeLink {
public:
	CollectorNode();

	void SendConfigAdvertise( byte destination, byte* config, byte length);

	// This mimics the 'setup' method of the arduino program.
	void setup();

	// This mimics the 'loop' method of the arduino program.
	void loop();

	virtual ~CollectorNode();
protected:

	// This will handle a
	void handleConfigSolicit( byte node );
	void handleConfigAccept (byte node );
	void handleConfigReject (byte node );

};

}

#endif /* COLLECTORNODE_H_ */
