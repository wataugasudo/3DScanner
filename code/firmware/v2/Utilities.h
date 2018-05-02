#ifndef HEADER_UTILITIES
#define HEADER_UTILITIES

#include "Arduino.h"

class Utilities {
    private:
    public:
        struct CalMap {
            int inLow;
            int inHigh;
            int outLow;
            int outHigh;

            void serialPrint() {
                Serial.println(inLow);
                Serial.println(inHigh);
                Serial.println(outLow);
                Serial.println(outHigh);
            }
        };
};

#endif
