
// interface
#include "sonar.h"
#include "config.h"
#include "leds.h"


// PORTD PIN7 = trig
// PORTC PIN2 = echo


void sonar__init() {
#if ENABLE_SONAR == ON
    DDRD |= (1 << 7);
    DDRC &= ~(1 << 2);
#endif
}


inches_t sonar__read() {
#if ENABLE_SONAR == ON

    // send a naieve trigger pulse, 10 us pulse

    PORTD |= 1 << 7;
    _delay_us(10);
    PORTD &= ~(1 << 7);

    // wait until echo goes high
    while ((PINC & (1 << 2)) == 0)
        ;

    // wait until echo goes low
    register int count = 1;  // start at one due to polling delay from above
    do {
        count++;
        _delay_us(1);
    } while ((PINC & (1 << 2)) != 0);

    // convert to inches,
    // https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
    return ((inches_t)count) / 148.0;
#endif
}
