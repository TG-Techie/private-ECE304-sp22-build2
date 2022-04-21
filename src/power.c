
#include "power.h"

//#include "Arduino.h"

#define SWITCH         A2  // pin 25 on atmega chip, PC2 on arduino
#define DELAY          10000
#define SWITCH_PINMASK (1 << 2)


void power__init() {
    // set the pin as an input, pull-down added in hardware
    DDRC &= ~SWITCH_PINMASK;  // Setting switch as an input
    PORTC = SWITCH_PINMASK;   // set pullup on PC2
    // pinMode(SWITCH, INPUT);
}

void power__wait_for_wake() {
    // wait for the switch to be pressed
    while ((PINC & SWITCH_PINMASK) == 0) {
    }
    // while (digitalRead(SWITCH) == LOW) {
    // }
}
