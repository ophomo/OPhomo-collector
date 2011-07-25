// What we want to create here.
#include "JeeNode.h"
#include "DallasPlug.h"
#include "DallasTemperatureSensor.h"

OPhomo::JeeNode node;
OPhomo::DallasPlug* dallasPlug;

void setup(void) {
	Serial.begin(57600);
	Serial.print("\n[OPHOMO JEENODE]");
	dallasPlug = new OPhomo::DallasPlug(&node.getPort1());
	Serial.print("\n[Created the DallasPlug]");
	dallasPlug->EnableDigitalPin();
	dallasPlug->EnableAnalogPin();
	dallasPlug->Search();
	Serial.print("\n[Searched the DallasPlug devices]");
}
;

void loop(void) {
	// call sensors.requestTemperatures() to issue a global temperature
	// request to all devices on the bus
	Serial.print("\n[Found ");
	Serial.print((int) dallasPlug->GetDeviceCount());
	Serial.print(" devices] ");
	Serial.println("\n[Requesting temperatures]");
	dallasPlug->RequestTemperatures();
	OPhomo::OneWireSensorFactory::WaitForConversion(
			dallasPlug->GetMaxConversionDelay());
	for (int i = 0; i < dallasPlug->GetDeviceCount(); i++) {
		OPhomo::TemperatureSensorData result;
		OPhomo::DallasTemperatureSensor
				* sensor =
						(OPhomo::DallasTemperatureSensor*) (dallasPlug->GetSensors()[i]);
		if (sensor)
			result = sensor->ReadTemperature();
		Serial.print("Sensor ");
		Serial.print((int) i);
		Serial.print(" has value ");
		Serial.println(result.GetCelsius());
	}
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
