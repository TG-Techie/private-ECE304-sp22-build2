#include "shared.h"

#include "leds.h"

int main() {
    leds__init();

    for (;;) {
        _delay_ms(1000);
        leds__green();
        _delay_ms(1000);
        leds__red();
    }

    return 0;
}