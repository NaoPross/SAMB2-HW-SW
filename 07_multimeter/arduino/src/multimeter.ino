#include <Arduino.h>

// Known resitor of the two (in ohms)
#define KNOWN_R 4700.0

// Voltage of the circuit (in volts)
#define KNOWN_V 5.0

// Pins definitions
#define P_VOLTMETER A0

const double STEP = KNOWN_V/1024;

void setup()
{
	Serial.begin(9600);
	pinMode(P_VOLTMETER, INPUT);
}

void loop()
{
	double raw_voltage = analogRead(P_VOLTMETER);
	double voltage     = raw_voltage*STEP;
	double current     = (KNOWN_V - voltage)/KNOWN_R;
	double resistor    = voltage/current;

	// String message = "Reading:\n\tVoltage:" + voltage + "\n\tCurrent:" + current + "\n\tResistor:" + resistor;
	// Serial.println(message);
	Serial.println("Reading:");

	Serial.print("\tVoltage:");
	Serial.println(voltage, 2);

	Serial.print("\tCurrent:");
	Serial.println(current, 2);

	Serial.print("\tResistor:");
	Serial.println(resistor, 2);

	delay(500);
}
