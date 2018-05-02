// Set sensor pins
const int trigPin = A0;
const int echoPin = A1;

// Constants
const float offset = 0; // error compensation (mm)
const float mach1 = 343; // speed of sound in m/s

// Init vars
float pingTime; // ping time (sensor => target => sensor)
float distance; // distance to target in mm

void setup() {
	// Set pinModes
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	Serial.begin(9600); // init serial readout @ 9600 baud
}

void loop() {
	// Reset trigger
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);

	// Trigger a ping
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// Read pingTime & calc distance
	pingTime = pulseIn(echoPin, HIGH); // read pingTime(us) => secs (1M us/sec)
	distance = pingTime*0.343/2; // compensate for error

	// Print distance(mm) over serial console
	Serial.println(distance);
}
