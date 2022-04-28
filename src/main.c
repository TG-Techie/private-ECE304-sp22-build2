#include "shared.h"
#include "config.h"


#include "leds.h"
#include "sevenseg.h"
#include "oled.h"
#include "power.h"
#include "sonar.h"
#include "smoothing.h"
#include "tracker.h"

// --- setup loop vars ---
track__status_t last_status = out_of_range;
smooth__smoother_t smoother;
track__tracker_t tracker;

// track__init(&tracker);

/* ---------- setup ---------- */
void main() {
    // --- init oled and power for life signs then sleep/wake ---
    oled__init();
    power__init();
    power__wait_for_wake();

    // --- init global vars ---
    smooth__init(&smoother);
    // track__init(&tracker);

    // --- initialize all modules ---
    leds__init();
    ss__init();
    sonar__init();

    // --- start ---
    leds__both();

    ss__set_value(12 * 1 + 1);

    // --- main loop ---
    for (int loop_n = 0;; loop_n++) {
        ss__refresh();


        // only refresh sornar every n loops
        if (0 == (loop_n % LOOP_SONAR_REFRESH_EVERY_N_LOOPS)) {
            inches_t raw_dist = sonar__read();

            // --- handle invalid distance ---
            // here we continue and skip it, but we printed in Arduino
            if (raw_dist == INVALID_SONAR_READ) {
                // ss__set_value_none();
                continue;
            }

            // --- filter the data
            // add to the smoother list
            smooth__insert(&smoother, raw_dist);
            inches_t dist = smooth__get_smoothed(&smoother);


            // --- register with the tracking system ---
            track__new_dist(&tracker, dist);

            // update outputs
            ss__set_value(dist);

            switch (tracker.status) {
                case out_of_range:
                    leds__off();
                    ss__set_value_none();
                    break;
                case too_far:
                    leds__green();
                    break;
                case just_right:
                    leds__off();
                    break;
                case too_close:
                    leds__red();
                    break;
                default:
                    leds__both();
                    // ss__set_value_none();
                    break;
            }

            // update the oled
            if ((tracker.status != last_status) || FORCE_OLED_REFRESH) {
                oled__refresh(
                    tracker.total_event_count,
                    tracker.unsafe_event_count,
                    tracker.closest_events,
                    4);
                last_status = tracker.status;
            }
        }
    }
}
