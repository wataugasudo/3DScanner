#ifndef HEADER_CONFIGURATION
#define HEADER_CONFIGURATION

////////// BASICS (Kinematics, Calibration, ETC) //////////

#define BAUD_RATE 9600

#define SCANNER_NAME "3D Scanner"

// Motion Constants
#define R_SPEED 500.0
#define Z_HOME_SPEED 1000.0
#define Z_SPEED 500.0
#define Z_ACCEL 1000.0
#define Z_MAX 10000

// Stepper Calibration
#define Z_STEPS_PER_UNIT 25 // ~8mm per rev; 200 steps per rev (full step)
#define R_STEPS_PER_REV 4076 // 4075.7728 is exact value

// Ultrasonic Calibration
// #define SENSOR_RAW_LOW
// #define SENSOR_RAW_HIGH
// #define SENSOR_CAL_LOW
// #define SENSOR_CAL_HIGH

////////// ADVANCED (Hookup Config) //////////

// Stepper Motors
#define R_1 2 // control pins ("IN" pins on driver)
#define R_2 3
#define R_3 4
#define R_4 5

#define Z_EN 8
#define Z_STEP 9 // control pins
#define Z_DIR 10
#define Z_HOME A7 // limit switch

// Ultrasonic Sensors
#define H_TRIG A14
#define H_ECHO A15
#define V_TRIG A12
#define V_ECHO A13

// Click Encoder
#define ENC_SW A0
#define ENC_DT A1
#define ENC_CLK A2
#define ENC_STEPS_PER_NOTCH 4

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
