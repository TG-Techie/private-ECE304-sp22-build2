#include "shared.h"
#include "config.h"


#include "leds.h"
#include "sevenseg.h"
#include "oled.h"
#include "power.h"
#include "sonar.h"


/* ---------- setup ---------- */
int main() {
    // --- init oled and power for life signs then sleep/wake ---
    oled__init();
    power__init();
    power__wait_for_wake();

    // --- initialize all modules ---
    leds__init();
    ss__init();
    sonar__init();
    // track__init();


    // --- test values ---
    ss__set_value(103);
    leds__both();
    oled__refresh(10, 3, NULL, 0);


    // --- shared loop variables ---
    for (int loop_n = 0;; loop_n++) {
        ss__refresh();

        // if (loop_n % LOOP_SONAR_REFRESH_EVERY_N_LOOPS == 0) {
        //     ss__set_value(sonar__read());
        // }
    }

    return 0;
}
