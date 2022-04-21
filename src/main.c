#include "shared.h"

#include "leds.h"

int main() {
    leds__init();
    leds__both();


    // for (;;) {
    //     _delay_ms(1000);
    //     leds__green();
    //     _delay_ms(1000);
    //     leds__red();
    // }

    return 0;
}