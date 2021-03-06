
// interface
#include "config.h"
#include "tracker.h"

// #include "HardwareSerial.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

// file-only define for clarity
#define TRACKER_N_ROLLING_SAMPLES 4
#define N_SAMPLES_WITH_NEW        ((int)(TRACKER_N_ROLLING_SAMPLES + 1))


char* track__status_to_string(track__status_t stat) {
    switch (stat) {
        case too_close:
            return (char*)_too_close_str;
        case just_right:
            return (char*)_just_right_str;
        case too_far:
            return (char*)_too_far_str;
        case out_of_range:
            return (char*)_out_of_range_str;
        default:
            return (char*)_unknown_str;
    }
}

// -- internal prototypes --
#if ENABLE_SMOOTHING == ON
void end_interaction(track__tracker_t* tracker);
void mark_interaction_unsafe(track__tracker_t* tracker);
void start_interaction(track__tracker_t* tracker);
void _reset_state(track__tracker_t* tracker);
track__status_t _get_status(inches_t dist);
void _insert_possible_new_closest(inches_t* events, inches_t closest);
#endif
// -- external implementation --

void track__init(track__tracker_t* const tracker) {
#if ENABLE_TRACKING == OFF
    return;
#else
    debug_print("track__init(...)... ");
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
    // debug_println("done");
#endif
}

inches_t track__new_dist(track__tracker_t* tracker, inches_t dist) {
#if ENABLE_TRACKING == OFF
    return dist;
#else
    // --- data detection ---
    track__status_t prev_stat = tracker->status;

    track__status_t stat = _get_status(dist);
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

    // set the closest for this engagment to min of closest and avg
    tracker->closest = min(tracker->closest, dist);

    return dist;
#endif
}

#if ENABLE_TRACKING == ON
// --- internal implementation ---


// -- internal funtion --
void _reset_state(track__tracker_t* tracker) {
    tracker->status         = out_of_range;
    tracker->closest        = LARGE_DIST;
    tracker->entered_unsafe = false;
    tracker->in_interaction = false;
}

// ------ extern functions ------

void start_interaction(track__tracker_t* tracker) {
    // do nothing if already in interaction
    if (tracker->in_interaction) return;

    // else start
    debug_println("start_interaction(...)");
    tracker->total_event_count += 1;
    tracker->in_interaction = true;
}

void mark_interaction_unsafe(track__tracker_t* tracker) {
    debug_println("mark_interaction_unsafe(...)");
    // increase the unsafe event count and mark the interaction as unsafe
    if (!(tracker->entered_unsafe)) {
        debug_println(" is marked as unsafe");
        tracker->entered_unsafe = true;
        tracker->unsafe_event_count += 1;
    }
}

void end_interaction(track__tracker_t* tracker) {
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

/* private */

track__status_t _get_status(inches_t dist) {  // TODO: why is this erroring?

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
#endif

#undef min
#undef N_SAMPLES_WITH_NEW
