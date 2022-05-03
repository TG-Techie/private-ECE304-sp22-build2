/* leds.c */

#include "leds.h"
#include "tracker.h"
#include "config.h"

/*
 * RED = arduino A0 = pc0 (pin 23)
 * GREEN = arduino A1 = pc1 (pin 24)
 */

#define RED_PINMASK   (1 << 1)
#define GREEN_PINMASK (1 << 0)

void leds__setstatus_from(track__status_t status) {
    // update outputs
    switch (status) {
        case out_of_range:
            leds__off();
            break;
        case too_far:
            leds__green();
            break;
        case just_right:
            leds__off();
            break;
        case too_close:
            leds__red();
            break;
        default:
            leds__both();
            break;
    }
}


void leds__init() {
#if ENABLE_LEDS == ON
    // setting LEDs as output pins
    DDRC |= RED_PINMASK | GREEN_PINMASK;  // makes first and second pins of PORTC outputs

    // pinMode(RED, OUTPUT);
    // pinMode(GREEN, OUTPUT);
    leds__off();
#endif
}
void leds__off() {
#if ENABLE_LEDS == ON
    // setting LEDs as low (turning them off)
    PORTC &= ~0x03;  // turn off both LEDs
    // analogWrite(RED, 0);
    // analogWrite(GREEN, 0);
#endif
}
void leds__green() {
#if ENABLE_LEDS == ON
    // only turn on green LED
    // analogWrite(RED, 0);
    // analogWrite(GREEN, 255);
    PORTC |= RED_PINMASK;     // turns on green LED
    PORTC &= ~GREEN_PINMASK;  // turns off red LED

#endif
}
void leds__red() {
#if ENABLE_LEDS == ON
    // only turn on red LED
    // analogWrite(RED, 255);
    // analogWrite(GREEN, 0);
    PORTC |= GREEN_PINMASK;  // turns on green LED
    PORTC &= ~RED_PINMASK;   // turns off  red LED
#endif
}
void leds__both() {
#if ENABLE_LEDS == ON
    // turn on both LEDs
    // analogWrite(RED, 255);
    // analogWrite(GREEN, 255);
    PORTC |= 0x03;  // turn on both LEDs
#endif
}
