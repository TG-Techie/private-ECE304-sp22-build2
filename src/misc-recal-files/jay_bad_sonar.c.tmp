
// interface
#include "sonar.h"
#include "config.h"
#include "leds.h"


// PORTD PIN7 = trig
// PORTC PIN2 = echo

// #define US_PER_INCH 148
// #define US_PER_CM   58

void sonar__init() {
    DDRD |= (1 << 7);
    DDRC &= ~(1 << 2);
}

inches_t sonar__read() {
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
        count += 1;
        _delay_us(1);
        // if (count > (US_PER_INCH * 10 * 12))
        //     return INVALID_SONAR_READ;
    } while ((PINC & (1 << 2)) != 0);

    // convert to inches,
    // https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
    inches_t dist = ((inches_t)count) / 148;

    if (dist <= 2) {
        return INVALID_SONAR_READ;
    }

    return dist;
}
