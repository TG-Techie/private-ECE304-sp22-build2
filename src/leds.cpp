// interface
#include "leds.h"

#include "Arduino.h"

#define RED   A0
#define GREEN A1


namespace leds {

void init() {
#if LEDS == ON
    // setting LEDs as output pins
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    off();
#endif
}
void off() {
#if LEDS == ON
    // setting LEDs as low (turning them off)
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
#endif
}
void green() {
#if LEDS == ON
    // only turn on green LED
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
#endif
}
void red() {
#if LEDS == ON
    // only turn on red LED
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
#endif
}
void both() {
#if LEDS == ON
    // turn on both LEDs
    analogWrite(RED, 255);
    analogWrite(GREEN, 255);
#endif
}
}  // namespace leds
