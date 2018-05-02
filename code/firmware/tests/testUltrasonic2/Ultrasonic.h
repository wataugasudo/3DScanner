#ifndef HEADER_ULTRASONIC
#define HEADER_ULTRASONIC

#include "Utilities.h"

class Ultrasonic {
    private:
        // dist(mm) = ping(uS) * [1(s)/1M(uS)]*[343(m/s)]*[1000(mm/m)]*[1/2]
        // const float PING_US_TO_DIST_MM = 0.1715;
        const int PING_DELAY_MS = 4;
        const int MAX_PING_TIME; // cutoff value to prevent error/delay (ms)
        const uint8_t TRIG_PIN;
        const uint8_t ECHO_PIN;
        Utilities::CalMap calMap;
        int read_raw();

    public:
        Ultrasonic(uint8_t _trigPin, uint8_t _echoPin);
        Ultrasonic(uint8_t _trigPin, uint8_t _echoPin, int _maxPing, Utilities::CalMap _calMap);
        void calibrate(int dist, bool highRange);
        Utilities::CalMap getMap();
        int read();
        int read(int pings);
};

#endif
