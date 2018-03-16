#include <AccelStepper.h>
#include <LiquidCrystal.h>
#define HALFSTEP 8

// Constants
const float R_SPEED = 100.0;
const float Z_SPEED = 1000.0;
const float Z_ACCEL = 1000.0;
const long Z_MAX = 10000;

// Defs
#define SW_MODE 54 // A0
#define SW_DOWN 55 // A1
#define SW_UP 56 // A2

// Init Steppers (28BYJ-48 w/ ULN2003 Drivers)
// (step, IN1, IN3, IN2, IN4)
AccelStepper mtrR(HALFSTEP, 2, 4, 3, 5); // turntable stepper
AccelStepper mtrZ(HALFSTEP, 6, 8, 7, 9); // z-axis stepper

// Init LiquidCrystal for display
// (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(16, 17, 18, 19, 20, 21);

void setup() {
    // setup control interface (LOW => pressed)
    pinMode(SW_MODE, INPUT_PULLUP); // mode switch
    pinMode(SW_DOWN, INPUT_PULLUP); // manual y-axis down
    pinMode(SW_UP, INPUT_PULLUP); // manual y-axis up

    // setup R for const speed
    mtrR.setMaxSpeed(R_SPEED);
    mtrR.setSpeed(R_SPEED);

    // setup Z for oscillating accel (starts going up)
    mtrZ.setMaxSpeed(Z_SPEED);
    mtrZ.setSpeed(Z_SPEED);
    mtrZ.setAcceleration(Z_ACCEL);
    mtrZ.moveTo(Z_MAX);

    // start LCD
    lcd.begin(16, 2); // set columns, rows
    lcd.print("Now Scanning...");
}

void loop() {
    // run R at const speed
    mtrR.runSpeed();

    // run Z depending on mode (demo/manual)
    if (digitalRead(SW_MODE) == HIGH) {
        //lcd.print("Now Scanning...");
        // run Z between 0 & Z_MAX
        if (mtrZ.distanceToGo() == 0) {
            if (mtrZ.currentPosition() == Z_MAX) {
                mtrZ.moveTo(0);
            } else {
                mtrZ.moveTo(Z_MAX);
            }
        }
    } else {
        //lcd.print("Down / Up\nBoth: Set Home");
        // run Z manually w/ SW_UP/DOWN buttons (both to set new 0)
        if (digitalRead(SW_DOWN) == LOW && digitalRead(SW_UP) == LOW) {
            mtrZ.setCurrentPosition(0);
            mtrZ.setSpeed(Z_SPEED);
        } else if (digitalRead(SW_DOWN) == LOW) {
            mtrZ.move(-Z_SPEED);
        } else if (digitalRead(SW_UP) == LOW) {
            mtrZ.move(Z_SPEED);
        } else {
            mtrZ.move(0);
        }
    }
    mtrZ.run();
}
