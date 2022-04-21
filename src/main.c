#include "shared.h"
#include "config.h"


#include "leds.h"
#include "sevenseg.h"
#include "oled.h"


/* ---------- setup ---------- */
void main() {
    // --- initialize all modules ---
    leds__init();
    ss__init();
    oled__init();
    // track__init();
    power__init();

    // --- test values ---
    ss__set_value(103);

    // --- shared loop variables ---

    // loop
    for (int loop_n = 0;; loop_n++) {
        _delay_ms(LOOP_DELAY_MS);
    }
}
