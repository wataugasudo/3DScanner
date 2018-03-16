#include <AccelStepper.h>
#define HALFSTEP 8

// Constants
const float R_SPEED = 500.0;
const float Z_SPEED = 1000.0;
const float Z_ACCEL = 1000.0;
const long Z_MAX = 10000;

// Init AccelStepper for 28BYJ-48 steppers w/ ULN2003 Drivers
// (step, IN1, IN3, IN2, IN4)
AccelStepper mtrR(HALFSTEP, 2, 4, 3, 5); // turntable stepper
AccelStepper mtrZ(HALFSTEP, 6, 8, 7, 9); // z-axis stepper

void setup() {
    // setup R for const speed
    mtrR.setMaxSpeed(R_SPEED);
    mtrR.setSpeed(R_SPEED);

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
