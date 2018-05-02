#include "Arduino.h"
#include "Ultrasonic.h"
#include "Utilities.h"

// For raw readings or on-the-fly calibration
Ultrasonic::Ultrasonic(uint8_t _trigPin, uint8_t _echoPin)
: TRIG_PIN(_trigPin), ECHO_PIN(_echoPin), MAX_PING_TIME(10000), calMap({0, 100, 0, 100}) {
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
}

// For pre-calibrated sensors
Ultrasonic::Ultrasonic(uint8_t _trigPin, uint8_t _echoPin, int _maxPing, Utilities::CalMap _calMap)
: TRIG_PIN(_trigPin), ECHO_PIN(_echoPin), MAX_PING_TIME(_maxPing), calMap(_calMap) {
	pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
}

// Calibrates a fixed reading point to its actual [dist]
// Run 2x w/ [highRange] @ true and false to calibrate
void Ultrasonic::calibrate(int dist, bool highRange) {
	if (highRange) {
		calMap.inHigh = read_raw();
		calMap.outHigh = dist;
	} else {
		calMap.inLow = read_raw();
		calMap.outLow = dist;
	}
}

// Get the current calibration mapping values
Utilities::CalMap Ultrasonic::getMap() {
	return calMap;
}

// Returns the theoretical distance from sensor (uncalibrated)
int Ultrasonic::read_raw() {
	// Reset trigger
	digitalWrite(TRIG_PIN, LOW);
	delayMicroseconds(2);

	// Trigger a ping
	digitalWrite(TRIG_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW);

	// Read pingTime (vals above MAX_PING_TIME lock to 0)
	return pulseIn(ECHO_PIN, HIGH, MAX_PING_TIME);
}

// Returns the calibrated distance from the sensor
int Ultrasonic::read() {
	int raw = read_raw();
	return (raw == 0) ? 0 : map(read_raw(), calMap.inLow, calMap.inHigh, calMap.outLow, calMap.outHigh);
}

// Returns the average of [pings] calibrated readings from the sensor
int Ultrasonic::read(int pings) {
	int sum = 0;
	for (int i = 0; i < pings; i++) {
		sum += read();
		delay(PING_DELAY_MS);
	}
	return (sum / pings);
}
