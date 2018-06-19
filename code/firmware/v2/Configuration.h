#ifndef HEADER_CONFIGURATION
#define HEADER_CONFIGURATION

#include "Arduino.h"

#define BAUD_RATE 9600
#define SCANNER_NAME "3D Scanner" // Max 16 Chars (w/ 16x2 display)

/*
NOTES:
- For our purposes, all generic "units" are in mm
*/

////////// RUN MODE //////////
/* Allows One-Touch Demo for TSA Judging - Power on will:
- home z-axis
- start scan without serial readout
- display "demo", action messages, and coordinates of scan
*/
#define DEMO_MODE // comment out to run in normal mode

////////// RESOLUTION //////////

#define Z_UNITS_PER_READ 1
#define R_DEGREES_PER_READ 10 // even divisor of 360
#define SENSOR_SAMPLES_PER_READ 20

////////// KINEMATICS //////////

#define R_SPEED 500.0
#define R_ACCEL 1000.0
#define Z_HOME_SPEED 750.0
#define Z_SPEED 500.0
#define Z_ACCEL 1500.0
#define Z_MAX_UNITS 160

////////// CALIBRATION //////////

// Steppers
#define Z_STEPS_PER_UNIT 25 // ~8mm per rev; 200 steps per rev (full step)
#define R_STEPS_PER_REV 4076 // 4075.7728 is exact value

// Ultrasonic
#define H_MAX_PING 2000
#define H_RAW_LOW 330
#define H_RAW_HIGH 810
#define H_CAL_LOW 60
#define H_CAL_HIGH 150

#define V_MAX_PING 2000
#define V_RAW_LOW 330
#define V_RAW_HIGH 810
#define V_CAL_LOW 60
#define V_CAL_HIGH 150

// Click Encoder
#define ENC_STEPS_PER_NOTCH 4

////////// HOOKUP CONFIG //////////

// Stepper Motors
#define R_1 2 // control pins ("IN" pins on driver)
#define R_2 3
#define R_3 4
#define R_4 5

#define Z_EN 8
#define Z_STEP 9 // control pins
#define Z_DIR 10
#define Z_HOME A15 // limit switch

// Ultrasonic Sensors
#define H_TRIG A6
#define H_ECHO A7
#define V_TRIG A4
#define V_ECHO A5

// Click Encoder
#define ENC_SW A0
#define ENC_DT A1
#define ENC_CLK A2

// LCD Interface
#define LCD_RS 16
#define LCD_EN 17
#define LCD_D4 18
#define LCD_D5 19
#define LCD_D6 20
#define LCD_D7 21

// Status LEDs
#define LED_READY A8
#define LED_WORKING A9
#define LED_STOP A10

#endif
