


// #include "Arduino.h"
// #include "HardwareSerial.h"


// -- data types and config --
#include "shared.h"

/* ------- local includes ------- */
// always needed
#include "leds.h"
#include "sonar.h"
#include "tracker.h"
// feature toggle includes

#if POWER == ON
#    include "power.h"
#endif

#if SMOOTHING == ON
#    include "smoothing.h"
#endif

#if SEVEN_SEG == ON
#    include "seven_seg.h"
#endif


#if OLED == ON
#    include "oled.h"
#endif


/* -------------------------------- global variables -------------------------------- */
track__tracker_t tracker;
int loop_number = 0;

// only update the oled if the status changes
#if OLED == ON
track__status_t last_status = track__out_of_range;
#endif

#if SMOOTHING == ON
smooth::smoother_t smoother;
#endif

/* --------------------------------- business logic --------------------------------- */

/* -------------- setup -------------- */

void setup() {
    // -- setup --
    if (Serial_debug) {
        Serial.begin(38400);
        while (!Serial) {
            ;  // wait for serial port to connect. Needed for native USB
        }
    }

    debug_println(" -- starting init --");

    delay(100);

// TODO: led init
#if OLED == ON
    oled::init();
#endif

#if POWER == ON
    power::init();
    power::wait_for_wake();
#endif

    sonar::init();
    track__init(&tracker);

#if SEVEN_SEG == ON
    seven_seg::init();
#endif

#if SMOOTHING == ON
    smooth::init(&smoother);
#endif

#if LEDS == ON
    leds::init();
#endif


    // -- end init --
    debug_println(" -- init done -- ");
}


/* -------------- loop -------------- */
void loop() {
    // step 0, refresh the seven segment display, update loop number
    loop_number = (loop_number + 1) % LOOP_ITEATIONS_BETWEEN_SONAR_READS;
#if SEVEN_SEG == ON
    seven_seg::refresh();
#endif  // SEVEN_SEG


    // only sample and update if it is time
    if (loop_number == 0) {  // step 1: read sonar, bail if bad


        // inches_t raw_dist = sonar::read();
        inches_t raw_dist = sonar::read_raw_cm() / 2.54;

        if (raw_dist == INVALID_DIST) {
            debug_println(" -- invalid distance --");
            // seven_seg::set_value(seven_seg::none);
            return;
        }

// step 2: smooth the distance
#if SMOOTHING == ON
        smooth::insert(&smoother, raw_dist);
        inches_t dist = smooth::get_smoothed(&smoother);
#else
        inches_t dist = raw_dist;  // TODO: add the smoothing code
#endif  // SMOOTHING

        // step 3: update tracker
        track__new_dist(&tracker, dist);


        // step 4: update the oled display
#if OLED == ON
        if ((tracker.status != last_status) || FORCE_OLED_REFRESH) {
            oled::update(&tracker);
            last_status = tracker.status;
        }
#endif  // OLED


        if (tracker.status == track__out_of_range) {
            leds::off();
#if SEVEN_SEG == ON
            seven_seg::set_value(seven_seg::none);
#endif  // SEVEN_SEG
        } else {
            if (tracker.status == track__just_right) leds::off();
            if (tracker.status == track__too_close) leds::red();
            if (tracker.status == track__too_far) leds::green();
#if SEVEN_SEG == ON
            seven_seg::set_value(dist);
#endif  // SEVEN_SEG
        }


        // step 5. display the results for debugging
        debug_print("feet: ");
        debug_print(dist / 12);
        debug_print(", \tstatus: ");
        debug_print(track__status_to_string(tracker.status));
        debug_println();
    }
}