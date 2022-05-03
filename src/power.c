
#include "power.h"
#include "sonar.h"
#include "board.h"
#include "leds.h"

void power__init() {
#if ENABLE_POWER == ON
    leds__init();
    sonar__init();
#endif
}

void power__wait_for_wake() {
#if ENABLE_POWER == ON
    // wait for the switch to be pressed
    inches_t reading;
    int count;
    bool led;
    do {
        _delay_ms(50);
        reading = sonar__read();
        if ((count++) % 25) {
            led = !led;
            setOut(redLedPin, led);
        };
    } while (reading < 12 || reading > 24);

#endif
}
