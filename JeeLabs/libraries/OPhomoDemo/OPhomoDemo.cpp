// What we want to create here.
#include "JeeNode.h"
#include "DallasPlug.h"
#include "DallasTemperatureSensor.h"
#include "ConsoleMeasurementHandler.h"

OPhomo::JeeNode node;
OPhomo::DallasPlug* dallasPlug;

void setup(void) {
	Serial.begin(57600);
	Serial.print("\n[OPHOMO JEENODE]");
	dallasPlug = new OPhomo::DallasPlug(&node.getPort3());
	Serial.print("\n[Created the DallasPlug]");
	dallasPlug->EnableDigitalPin();
	dallasPlug->EnableAnalogPin();
	Serial.print("\n[Searched the DallasPlug devices]");
	Serial.print("\n[Found ");
	Serial.print((int) dallasPlug->Search());
	Serial.print(" devices] ");

}
;

void loop(void) {
	// call sensors.requestTemperatures() to issue a global temperature
	// request to all devices on the bus
	OPhomo::ConsoleMeasurementHandler handler;
	Serial.println("\n[Requesting temperatures]");
	Serial.println("\tStart conversion");
	uint16_t timeout = dallasPlug->InitReadAll();
	while ( timeout ) {
		timeout = dallasPlug->ReadAllAnalogSensors(&handler);
		timeout += dallasPlug->ReadAllDigitalSensors(&handler);
	}
	delay(5000);
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
