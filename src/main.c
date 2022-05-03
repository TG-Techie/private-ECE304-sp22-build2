#include "shared.h"
#include "config.h"


// #include "leds.h"
#include "sevenseg.h"
// #include "oled.h"
// #include "power.h"
// #include "sonar.h"
// #include "smoothing.h"
// #include "tracker.h"


#include "pinIO.h"
#include "board.h"


void main() {
    // setDir(sevenSegPort, OUTPUT);
    // setDir(digEnPort, OUTPUT);

    // // setOut(dig0En, 0);
    // setOut(sevenSegPort, 0xff);

    // for (uint8_t loop_num = 0;; loop_num++) {
    //     setOut(digEnPort, ~(0x01 << (loop_num % 3)));
    // }

    se__init();
    se__set_value(12 * 9 + 10);

    int value = 0;
    for (int16_t loop_num = 0;; loop_num++) {
        se__refresh();
    }
}


// // --- setup loop vars ---
// track__status_t last_status = out_of_range;
// smooth__smoother_t smoother;
// track__tracker_t tracker;

// // track__init(&tracker);

// /* ---------- setup ---------- */
// void main() { // w/ -Wno-main
//     // --- init oled and power for life signs then sleep/wake ---
//     oled__init();
//     power__init();
//     power__wait_for_wake();

//     // --- init global vars ---
//     smooth__init(&smoother);
//     // track__init(&tracker);

//     // --- initialize all modules ---
//     leds__init();
//     se__init();
//     sonar__init();

//     // --- start ---
//     leds__both();

//     se__set_value(12 * 1 + 1);


//     // --- main loop ---
//     for (int loop_n = 0;; loop_n++) {
//         se__refresh();


//         // only refresh sornar every n loops
//         if (0 == (loop_n % LOOP_SONAR_REFRESH_EVERY_N_LOOPS)) {
//             inches_t raw_dist = sonar__read();

//             // --- handle invalid distance ---
//             // here we continue and skip it, but we printed in Arduino
//             if (raw_dist == INVALID_SONAR_READ) {
//                 continue;
//             }

//             // --- filter the data
//             // add to the smoother list
//             inches_t dist = smooth(&smoother, raw_dist);

//             se__set_value(dist);

//             // --- register with the tracking system ---
//             track__new_dist(&tracker, dist);

//             // --- update output ---
//             leds__setstatus_from(tracker.status);
//             if (tracker.status == out_of_range) se__set_value_none();

//             // update the oled
//             if ((tracker.status != last_status) || FORCE_OLED_REFRESH) {
//                 oled__refresh(
//                     tracker.total_event_count,
//                     tracker.unsafe_event_count,
//                     tracker.closest_events,
//                     4);
//                 last_status = tracker.status;
//             }
//         }
//     }
// }
