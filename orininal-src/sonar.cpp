
// interface
#include "sonar.h"

#include <HCSR04.h>

#include "Arduino.h"

HCSR04 hc(12, 11);  // initialisation class HCSR04 (trig pin , echo pin)


namespace sonar {

void init() {
    debug_println("sonar::init()... done");
}


float read() {
    double cm     = hc.dist();
    double inches = cm / 2.54;
    return inches;
}

float read_raw_cm() {
    // TODO #define the pin to give them names
    digitalWrite(12, LOW);
    delayMicroseconds(2);
    digitalWrite(12, HIGH);
    delayMicroseconds(10);
    digitalWrite(12, LOW);
    noInterrupts();
    float d = pulseIn(11, HIGH, 23529.4);  // max sensor dist ~4m
    interrupts();
    return d / 58.8235;
}

}  // namespace sonar
