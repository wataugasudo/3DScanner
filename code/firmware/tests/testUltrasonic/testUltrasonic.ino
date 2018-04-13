// Set sensor pins
const int trigPin = 13; // sensor Trig pin => Arduino pin 13
const int echoPin = 11; // sensor Echo pin => Arduino pin 11

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
	delayMicroseconds(2000);

	// Trigger a ping
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(15);
	digitalWrite(trigPin, LOW);
	delayMicroseconds(10);

	// Read pingTime & calc distance
	pingTime = pulseIn(echoPin, HIGH) / 1000000; // read pingTime(us) => secs (1M us/sec)
	distance = (mach1 * pingTime) / 2; // calc distance(m) (ping dist / 2 = actual dist)
	distance *= 1000; // convert distance(m) => mm (1K mm/m)
	distance += offset; // compensate for error

	// Print distance(mm) over serial console
	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println("mm");
}
