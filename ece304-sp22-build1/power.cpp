
#include "power.h"

#include "Arduino.h"

#define SWITCH A2  // TODO: move to shared
#define DELAY  10000


namespace power {

void init() {
    // set the pin as an input, pull-down added in hardware
    pinMode(SWITCH, INPUT);
}

void wait_for_wake() {
    // wait for the switch to be pressed
    while (digitalRead(SWITCH) == LOW) {
    }
}


}  // namespace power
