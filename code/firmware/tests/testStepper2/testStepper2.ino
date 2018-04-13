#include <AccelStepper.h>

#define Z_EN 8

// Constants
const float R_SPEED = 500.0;
const float Z_SPEED = 500.0;
const float Z_ACCEL = 1000.0;
const long Z_MAX = 10000;

// Init 28BYJ-48 stepper w/ ULN2003 driver (halfH-4wire, IN1, IN3, IN2, IN4)
AccelStepper mtrR(AccelStepper::HALF4WIRE, 2, 4, 3, 5); // turntable stepper
// Init 17HS13-0404S stepper w/ A4988 driver (2wire, STEP, DIR) [VREF = 320mV]
AccelStepper mtrZ(AccelStepper::DRIVER, 9, 10); // z-axis stepper

void setup() {

    // setup R for const speed
    mtrR.setMaxSpeed(R_SPEED);
    mtrR.setSpeed(R_SPEED);

    // enable Z
    pinMode(Z_EN, OUTPUT);
    digitalWrite(Z_EN, HIGH);
    delay(1);

    // setup Z for oscillating accel (starts up)
    mtrZ.setMaxSpeed(Z_SPEED);
    mtrZ.setSpeed(Z_SPEED);
    mtrZ.setAcceleration(Z_ACCEL);
    mtrZ.moveTo(Z_MAX);
}

void loop() {
    // run R at const speed
    mtrR.runSpeed();

    // run Z between 0 & Z_MAX
    if (mtrZ.distanceToGo() == 0) {
        if (mtrZ.currentPosition() == Z_MAX) {
            mtrZ.moveTo(0);
        } else {
            mtrZ.moveTo(Z_MAX);
        }
    }
    mtrZ.run();
}
