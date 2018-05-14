// #include "Arduino.h"
// #include "libs/AccelStepper/src/AccelStepper.h"
// #include "Ultrasonic.h"
// #include "Configuration.h"
//
// // Init turntable stepper (28BYJ-48 w/ ULN2003 driver)
// AccelStepper mtrR(AccelStepper::HALF4WIRE, R_1, R_3, R_2, R_4);
// // Init z-axis stepper (17HS13-0404S w/ A4988 driver [VREF = 320mV])
// AccelStepper mtrZ(AccelStepper::DRIVER, Z_STEP, Z_DIR);
//
// // Init HC-SR04 ultrasonic sensors
// Ultrasonic probeH(H_TRIG, H_ECHO);
// Ultrasonic probeV(V_TRIG, V_ECHO);
//
// void scannerSetup() {
//     pinMode(Z_EN, OUTPUT);
// }
//
// void setZEnabled(bool enableZ) {
//     if (enableZ) {
//         digitalWrite(Z_EN, HIGH);
//         delay(1);
//     } else {
//         digitalWrite(Z_EN, LOW);
//     }
// }
//
// void home() {
//
// }
//
// void scan() {
//
// }
//
//
// //////////////////////////////// Replace below with home() and scan() above
//
//
// void setup() {
//     // setup R for const speed
//     mtrR.setMaxSpeed(R_SPEED);
//     mtrR.setSpeed(R_SPEED);
//
//     // enable Z
//     pinMode(Z_EN, OUTPUT);
//     digitalWrite(Z_EN, HIGH);
//     delay(1);
//
//     // setup Z for oscillating accel (starts up)
//     mtrZ.setMaxSpeed(Z_SPEED);
//     mtrZ.setSpeed(Z_SPEED);
//     mtrZ.setAcceleration(Z_ACCEL);
//     mtrZ.moveTo(Z_MAX);
// }
//
// void loop() {
//     // run R at const speed
//     mtrR.runSpeed();
//
//     // run Z between 0 & Z_MAX
//     if (mtrZ.distanceToGo() == 0) {
//         if (mtrZ.currentPosition() == Z_MAX) {
//             mtrZ.moveTo(0);
//         } else {
//             mtrZ.moveTo(Z_MAX);
//         }
//     }
//     mtrZ.run();
// }
