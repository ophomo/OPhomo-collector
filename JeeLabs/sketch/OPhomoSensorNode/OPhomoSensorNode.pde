/*
 * OPhomoCollectorNode.pde
 *
 *  Created on: Feb 18, 2011
 *      Author: dd@ophomo.org
 *
 * http://opensource.org/licenses/mit-license.php
 */
#include "WProgram.h"
#include "JeeNode.h"
#include "SensorNode.h"
#include "RF12Controller.h"
#include "DallasPlug.h"
#include "OneWireController.h"

#define VERSION "0.3.1"

using namespace OPhomo;

SensorNode node;
RF12Controller rf12Controller(node);
OneWireController oneWireController(node);


void setup(void) {
	Serial.begin(57600);
	Serial.print("\n[OPHOMO SENSORNODE v");
	Serial.print(VERSION);
	Serial.println( "]");
	node.setup();
}


void loop(void) {
	node.loop();
}

int main(void) {

	/* Must call init for arduino to work properly */
	init();

	/****************************/
	/* Add your setup code here */
	/****************************/
	setup();

	for (;;) {

		loop();

	} // end for

} // end main


