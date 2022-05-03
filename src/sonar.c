
// interface
#include "sonar.h"
#include "config.h"
#include "board.h"
#include "leds.h"


// PORTD PIN7 = trig
// PORTC PIN2 = echo

// #define US_PER_INCH 148
// #define US_PER_CM   58


void sonar__init() {
    _delay_ms(100);
    DDRD |= (1 << 7);
    DDRB &= ~(1 << 0);
}

inches_t sonar__read() {
    // send a naieve trigger pulse, 10 us pulse

    PORTB &= ~(1 << 0);
    _delay_us(5);
    PORTB |= (1 << 0);
    _delay_us(10);
    PORTB &= ~(1 << 0);


    while ((PIND & 0x80) == 0)  // wait until echo goes high
        ;


    // wait until echo goes low
    register int count = 1;  // start at one due to polling delay from above
    do {
        count += 1;
        _delay_us(1);
        // if (count > (US_PER_INCH * 10 * 12))
        //     return INVALID_SONAR_READ;
    } while ((PIND & 0x80) != 0);

    // convert to inches,
    // https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
    inches_t dist = ((inches_t)count) / 148;

    // hack
    dist *= 1.25;

    if (dist <= 2) {
        return INVALID_SONAR_READ;
    }

    return dist;
}
