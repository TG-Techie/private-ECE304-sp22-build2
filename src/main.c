#include "shared.h"
#include "config.h"


#include "leds.h"
#include "sevenseg.h"
#include "oled.h"
#include "power.h"


/* ---------- setup ---------- */
int main() {
    // --- initialize all modules ---
    oled__init();
    power__init();
    power__wait_for_wake();
    // // rest
    leds__init();
    ss__init();
    // sonar__init();
    // track__init();


    // --- test values ---
    ss__set_value(103);
    leds__both();
    oled__refresh(10, 3, NULL, 0);


    // --- shared loop variables ---
    for (int loop_n = 0;; loop_n++) {
        ss__refresh();

        // if (loop_n % 20 == 0) {
        //     oled__refresh(loop_n, loop_n, NULL, 0);
        // }
    }

    return 0;
}
