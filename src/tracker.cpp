
// interface
#include "tracker.h"

#include "HardwareSerial.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

// file-only define for clarity
#define N_SAMPLES_WITH_NEW ((int)(TRACKER_N_ROLLING_SAMPLES + 1))

namespace track {


char* status_to_string(status_t stat) {
    switch (stat) {
        case too_close:
            static const char too_close[] = "too_close";
            return (char*)too_close;
        case just_right:
            static const char just_right[] = "just_right";
            return (char*)just_right;
        case too_far:
            static const char too_far[] = "too_far";
            return (char*)too_far;
        case out_of_range:
            static const char out_of_range[] = "out_of_range";
            return (char*)out_of_range;
        default:
            static const char unknown[] = "unknown";
            return (char*)unknown;
    }
}

// -- internal prototypes --
status_t _get_status(inches_t dist);
void _insert_possible_new_closest(inches_t* events, inches_t closest);

// -- internal cuntion --
void _reset_state(tracker_t* tracker) {
    tracker->status         = out_of_range;
    tracker->closest        = LARGE_DIST;
    tracker->entered_unsafe = false;
    tracker->in_interaction = false;
}

// ------ extern functions ------

void start_interaction(tracker_t* tracker) {
    // do nothing if already in interaction
    if (tracker->in_interaction) return;

    // else start
    debug_println("start_interaction(...)");
    tracker->total_event_count += 1;
    tracker->in_interaction = true;
}

void mark_interaction_unsafe(tracker_t* tracker) {
    Serial.println("mark_interaction_unsafe(...)");
    // increase the unsafe event count and mark the interaction as unsafe
    if (!(tracker->entered_unsafe)) {
        Serial.println(" is marked as unsafe");
        tracker->entered_unsafe = true;
        tracker->unsafe_event_count += 1;
    }
}

void end_interaction(tracker_t* tracker) {
    // do nothing if not in interaction
    if (!(tracker->in_interaction)) return;

    // else end

    debug_println("end_interaction(...)");

    const inches_t closest = tracker->closest;
    inches_t* events       = tracker->closest_events;

    if (tracker->entered_unsafe) {
        // TODO: insert new closest if is unsafe and lower than what is there
        _insert_possible_new_closest(events, closest);
    }

    tracker->in_interaction = false;

    _reset_state(tracker);
}

// -- external implementation --

void init(tracker_t* const tracker) {
    debug_print("track::init(...)... ");
    /* -- state -- */
    _reset_state(tracker);
    /* -- over all time -- */
    tracker->total_event_count  = 0;
    tracker->unsafe_event_count = 0;
    // tracker->closest_events     = {0};
    // memset(tracker->closest_events, 0xff, sizeof(tracker->closest_events));
    // -- since we are hard coding this just for 4, plop in the values manually --
    tracker->closest_events[0] = TOMBSTONE_DIST;
    tracker->closest_events[1] = TOMBSTONE_DIST;
    tracker->closest_events[2] = TOMBSTONE_DIST;
    tracker->closest_events[3] = TOMBSTONE_DIST;
    debug_println("done");
}

inches_t new_dist(tracker_t* tracker, inches_t dist) {
    // --- data detection ---
    status_t prev_stat = tracker->status;

    status_t stat = _get_status(dist);
    debug_print("tracker -> stat = ");
    debug_println(status_to_string(stat));

    // --- state update ---
    // roll the previous data out and write the new state to the tracker
    tracker->status = stat;


    // --- event interpretation ---
    // TODO(Jay): implement this

    /*
     * enter too_close:
     *  - from too_far || out_of_range, start();
     *  - form anywhere, mark too close
     * enter just_right:
     * - from too_far || out_of_range, start();
     * - from too_close, pass
     * enter too_far:
     * - from too_close || just_right, end();
     * - from out_of_range, pass
     * enter out_of_range:
     * - from too_close || just_right, end();
     * - from too_far, pass
     */

    // if (stat == prev_stat)
    //     ;  // no change
    // else if (stat == too_close && (prev_stat >= too_far))
    //     start_interaction(tracker);
    //     mark_interaction_unsafe(tracker);
    // else if (stat == too_close && prev_stat == just_right)
    //     start_interaction(tracker);

    switch (stat) {
        case too_close:
            if (prev_stat >= too_far) start_interaction(tracker);
            mark_interaction_unsafe(tracker);
            break;
        case just_right:
            if (prev_stat >= too_far) start_interaction(tracker);
            break;
        case too_far:
            if (prev_stat <= just_right) end_interaction(tracker);
            break;
        case out_of_range:
            if (prev_stat <= just_right) end_interaction(tracker);
            break;
        default:
            /* unknown state transition */
            debug_print("unknown state transition ");
            debug_print(status_to_string(prev_stat));
            debug_print(" -> ");
            debug_println(status_to_string(stat));

            break;
    }

    // // no movement: same zone
    // if (prev_stat == stat)
    //     /* no movement, no action */;
    // else if (stat == just_right && prev_stat == too_far)
    //     start_interaction(tracker);
    // else if (stat == too_close && prev_stat == just_right)
    //     mark_interaction_unsafe(tracker);
    // else if (stat == just_right && prev_stat == too_close)
    //     /* exiting unsafe */;
    // else if ((stat == too_far ) || stat == out_of_range /* && <any other previous state> */)
    //     end_interaction(tracker);
    // else {
    //     /* unknown state transition */
    //     if (Serial_debug) {
    //         debug_print("unknown state transition ");
    //         debug_print(status_to_string(prev_stat));
    //         debug_print(" -> ");
    //         debug_println(status_to_string(stat));
    //     }
    // }


    // set the closest for this engagment to min of closest and avg
    tracker->closest = min(tracker->closest, dist);

    return dist;
}

// --- internal implementation ---

/* private */

status_t _get_status(inches_t dist) {  // TODO: why is this erroring?

    if (dist >= OUT_OF_RANGE_THRESHOLD)
        return out_of_range;
    else if (dist >= TOO_FAR_THRESHOLD)
        return too_far;
    else if (dist >= JUST_RIGHT_THRESHOLD)
        return just_right;
    else
        return too_close;


    //     if (dist <= TOO_CLOSE_THRESHOLD)
    //         return too_close;
    //     else if (TOO_CLOSE_THRESHOLD < dist && dist <= TOO_FAR_THRESHOLD)
    //         return just_right;
    //     else if (TOO_FAR_THRESHOLD < dist && dist <= OUT_OF_RANGE_THRESHOLD)
    //         return too_far;
    //     else if (dist >= OUT_OF_RANGE_THRESHOLD)
    //         return out_of_range;
    //     else  // default
    //         return out_of_range;
}

void _insert_possible_new_closest(inches_t* events, inches_t closest) {
    // loop over the events in the array, insert the new closest if it is lower and then shift the
    // rest forward dropping the oldest. the lenght of the array is: (drumroll please)
    // TRACKER_N_KEPT_UNSAFE_INTERACTION_DISTANCES

    bool inserted         = false;
    inches_t prev_closest = LARGE_DIST;
    for (int i = 0; i < TRACKER_N_KEPT_UNSAFE_INTERACTION_DISTANCES; i++) {
        inches_t event = events[i];
        if (!inserted && closest < event) {
            inserted     = true;
            prev_closest = event;
            events[i]    = closest;
        } else if (inserted) {
            events[i]    = prev_closest;
            prev_closest = event;
        }
    }
}

}  // namespace track


#undef N_SAMPLES_WITH_NEW