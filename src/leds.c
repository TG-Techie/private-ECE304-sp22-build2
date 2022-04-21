/* leds.c */

#include "leds.h"

#define RED   A0
#define GREEN A1

#define pinMode(...)
#define analogWrite(...)

void leds__init() {
#if LEDS == ON
    // setting LEDs as output pins
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    leds__off();
#endif
}
void leds__off() {
#if LEDS == ON
    // setting LEDs as low (turning them off)
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
#endif
}
void leds__green() {
#if LEDS == ON
    // only turn on green LED
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
#endif
}
void leds__red() {
#if LEDS == ON
    // only turn on red LED
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
#endif
}
void leds__both() {
#if LEDS == ON
    // turn on both LEDs
    analogWrite(RED, 255);
    analogWrite(GREEN, 255);
#endif
}
