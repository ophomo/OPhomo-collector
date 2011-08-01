#include <OneWire.h>
#include <stdlib.h>
#include <DallasTemperature.h>


/* DS18S20 Temperature chip i/o */

OneWire  portOne(4);  // on pin 4
OneWire  portTwo(5);  // on pin 5
DallasTemperature sensorsOne(&portOne);
DallasTemperature sensorsTwo(&portTwo);

enum NodeState {
  UNKNOWN_STATE = 0,
  CONFIGURATION_REQUEST_STATE,
  CONFIGURATION_RECEIVED_STATE,
  MEASURING_STATE,
  UPDATE_REQUEST_STATE,
  UPDATE_RECEIVED_STATE
};

// Currently, I only use the analog meaurement and the Dallas Sensors, but more can be added easily

#define SENSORTYPES 2
enum SensorType {
  UNKNOWN_SENSOR = 0,
  ANALOG_SENSOR,
  DALLAS_SENSOR
};

#define PORTTYPES 2
enum PortType {
  UNKNOWN_PORT_TYPE = 0,
  ANALOG_PORT_TYPE,
  DIGITAL_PORT_TYPE
};


bool ValidationMatrix[SENSORTYPES][PORTTYPES] =  { { true, false },{ true, true } };


void setup(void) {
    Serial.begin(57600);
    Serial.print("\n[OPHOMO JEENODE]");
    sensorsOne.begin();
    sensorsTwo.begin();
}


void loop(void) {
// call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensorsOne.requestTemperatures(); // Send the command to get temperatures
  sensorsTwo.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
   
  Serial.println("Temperature for Device 1 is: ");
  for (uint8_t i = 0; i < sensorsOne.getDeviceCount(); i++ ) {
    Serial.println(sensorsOne.getTempCByIndex(i)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire}
  }

  Serial.println("Temperature for Device 2 is: ");
  for (uint8_t i = 0; i < sensorsTwo.getDeviceCount(); i++ ) {
    Serial.println(sensorsTwo.getTempCByIndex(i)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire}
  }
}
