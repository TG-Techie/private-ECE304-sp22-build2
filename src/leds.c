/* leds.c */

#include "leds.h"
#include "tracker.h"
#include "config.h"
#include "board.h"

/*
 * RED = arduino A0 = pc0 (pin 23)
 * GREEN = arduino A1 = pc1 (pin 24)
 */


void leds__init() {
#if ENABLE_LEDS == ON
    // setting LEDs as output pins
    setDir(greenLedPin, OUTPUT);
    setDir(redLedPin, OUTPUT);
    leds__off();
#endif
}
void leds__off() {
#if ENABLE_LEDS == ON
    setOut(greenLedPin, LOW);
    setOut(redLedPin, LOW);
#endif
}
void leds__green() {
#if ENABLE_LEDS == ON
    setOut(greenLedPin, HIGH);
    setOut(redLedPin, LOW);
#endif
}
void leds__red() {
#if ENABLE_LEDS == ON
    setOut(greenLedPin, LOW);
    setOut(redLedPin, HIGH);
#endif
}
void leds__both() {
#if ENABLE_LEDS == ON
    setOut(greenLedPin, HIGH);
    setOut(redLedPin, HIGH);
#endif
}


void leds__setstatus_from(track__status_t status) {
    // update outputs
    switch (status) {
        case out_of_range:
            leds__green();  // leds__off();
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