#ifndef HEADER_ROUTINES
#define HEADER_ROUTINES

#include "Arduino.h"
#include "src/AccelStepper/src/AccelStepper.h"
#include "Utilities.h"
#include "Ultrasonic.h"
#include "Configuration.h"

class Routines {
    private:
        const int R_STEPS_PER_READ = (R_STEPS_PER_REV * R_DEGREES_PER_READ / 360);
        const int Z_STEPS_PER_READ = (Z_STEPS_PER_UNIT * Z_UNITS_PER_READ);
        // Ultrasonic sensors
        const Utilities::CalMap CAL_MAP_H = {H_RAW_LOW, H_RAW_HIGH, H_CAL_LOW, H_CAL_HIGH};
        const Utilities::CalMap CAL_MAP_V = {V_RAW_LOW, V_RAW_HIGH, V_CAL_LOW, V_CAL_HIGH};
        Ultrasonic sensorH;
        Ultrasonic sensorV;
        // Steppers
        AccelStepper mtrR;
        AccelStepper mtrZ;
        // Position counters
        int rPos;
        int zPos;
        void setZEnabled(bool enable);

    public:
        Routines();
        void home();
        void step();
        int getZ();
        int getR();
        int readH();
        int readV();
        void setLEDs(bool ready, bool working, bool stop);
};

#endif
