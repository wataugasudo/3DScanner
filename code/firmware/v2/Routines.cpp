#include "Arduino.h"
#include "Routines.h"
#include "src/AccelStepper/src/AccelStepper.h"
#include "Ultrasonic.h"
#include "Configuration.h"

// Inits all universal values & pinModes
Routines::Routines()
: sensorH(H_TRIG, H_ECHO, H_MAX_PING, CAL_MAP_H), // Construct HC-SR04 Sensors
sensorV(V_TRIG, V_ECHO, V_MAX_PING, CAL_MAP_V),
mtrR(AccelStepper::HALF4WIRE, R_1, R_3, R_2, R_4), // Construct turntable stepper (28BYJ-48 w/ ULN2003 driver)
mtrZ(AccelStepper::DRIVER, Z_STEP, Z_DIR) { // Construct z-axis stepper (17HS13-0404S w/ A4988 driver) [VREF = 320mV])
    pinMode(LED_READY, OUTPUT);
    pinMode(LED_WORKING, OUTPUT);
    pinMode(LED_STOP, OUTPUT);

    // Setup R
    mtrR.setMaxSpeed(R_SPEED);
    mtrR.setAcceleration(R_ACCEL);

    // Setup Z
    pinMode(Z_EN, OUTPUT);
    pinMode(Z_HOME, INPUT_PULLUP);
    mtrZ.setMaxSpeed((Z_SPEED > Z_HOME_SPEED ? Z_SPEED : Z_HOME_SPEED));
    mtrZ.setAcceleration(Z_ACCEL);
}

// Homes the Z-Axis & Zeroes position values
void Routines::home() {
    setLEDs(false, true, false);
    setZEnabled(true);
    mtrZ.setSpeed(Z_HOME_SPEED);
    while(digitalRead(Z_HOME)) {
        mtrZ.runSpeed();
    }
    mtrZ.stop();
    mtrZ.runToPosition();
    setZEnabled(false);
    zPos = 0;
    rPos = 0;
    setLEDs(true, false, false);
}

// Moves axes to the next reading position (incs either R or Z-Axis)
void Routines::step() {
    if (rPos < 360) {
        rPos += R_DEGREES_PER_READ;
        mtrR.move(R_STEPS_PER_READ);
        mtrR.runToPosition();
    } else {
        rPos = 0;
        zPos += Z_UNITS_PER_READ;
        setZEnabled(true);
        mtrZ.move(Z_STEPS_PER_READ);
        mtrZ.runToPosition();
        setZEnabled(false);
    }
}

// Returns the distance of the Z-Axis from the home position
int Routines::getZ() {
    return zPos;
}

// Returns the angle of the R-Axis from its initial position
int Routines::getR() {
    return rPos;
}

// Returns an averaged reading from the Horizontal probe
int Routines::readH() {
    return sensorH.read(SENSOR_SAMPLES_PER_READ);
}

// Returns an averaged reading from the Vertical probe
int Routines::readV() {
    return sensorV.read(SENSOR_SAMPLES_PER_READ);
}

// Sets the status LEDs - true for on, false for off [GYR]
void Routines::setLEDs(bool ready, bool working, bool stop) {
    digitalWrite(LED_READY, (ready ? HIGH : LOW));
    digitalWrite(LED_WORKING, (working ? HIGH : LOW));
    digitalWrite(LED_STOP, (stop ? HIGH : LOW));
}

// Sets whether the Z-Axis is enabled (true to move, false to save power)
void Routines::setZEnabled(bool enable) {
    if (enable) {
        digitalWrite(Z_EN, HIGH); // enable Z
        delay(1);
    } else {
        digitalWrite(Z_EN, LOW); // disable z (saves power)
    }
}
