
#include "power.h"

//#include "Arduino.h"

#define SWITCH         A2  // pin 25 on atmega chip, PC2 on arduino
#define DELAY          10000
#define SWITCH_PINMASK (1 << 2)


void power__init() {
#if ENABLE_POWER == ON
    // set the pin as an input, pull-down added in hardware
    DDRC &= ~SWITCH_PINMASK;  // Setting switch as an input
    // PORTC |= SWITCH_PINMASK;  // set pullup on PC2
// pinMode(SWITCH, INPUT);
#endif
}

void power__wait_for_wake() {
#if ENABLE_POWER == ON
    // wait for the switch to be pressed
    while ((PINC & SWITCH_PINMASK) == 0) {
    }
#endif
}
