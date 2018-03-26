#ifndef HEADER_ULTRASONIC
#define HEADER_ULTRASONIC

class Ultrasonic {
    private:
        // dist(mm) = ping(uS) * [1(s)/1M(uS)]*[343(m/s)]*[1000(mm/m)]*[1/2]
        const float PING_US_TO_DIST_MM = 0.1715;
        const int PING_DELAY_MS = 4;
        const uint8_t _trigPin;
        const uint8_t _echoPin;

    public:
        Ultrasonic(uint8_t trigPin, uint8_t echoPin);
        float read();
        float read_avg(int pings);
};

#endif
