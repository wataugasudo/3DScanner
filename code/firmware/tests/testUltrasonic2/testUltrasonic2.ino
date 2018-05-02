#include "Ultrasonic.h"
#include "Utilities.h"

Utilities::CalMap calMap = {330, 810, 60, 150};
Ultrasonic probe1(A0, A1, 2000, calMap);

void setup() {
    Serial.begin(9600);

    // Serial.println("1\" cal in 3s");
    // delay(3000);
    // probe1.calibrate(1, false);
    // Serial.println("5\" cal in 3s");
    // delay(3000);
    // probe1.calibrate(5, true);
    // Serial.println("Calibrated:");
    // probe1.getMap().serialPrint();
    // Serial.println("\n");
}

void loop() {
    Serial.println(probe1.read(20));
}
