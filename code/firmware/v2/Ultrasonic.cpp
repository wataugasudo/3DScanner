#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(uint8_t trigPin, uint8_t echoPin)
: _trigPin(trigPin), _echoPin(echoPin)
{
	pinMode(_trigPin, OUTPUT);
	pinMode(_echoPin, INPUT);
}

float Ultrasonic::read() {
	// Reset trigger
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	// Trigger a ping
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// Read pingTime & calc distance
	return (pulseIn(echoPin, HIGH) * PING_US_TO_DIST_MM);
}

float Ultrasonic::read_avg(int pings) {
	float sum = 0;
	for (int i = 0; i < pings; i++) {
		sum += read();
		delay(PING_DELAY_MS);
	}
	return (sum / pings);
}
