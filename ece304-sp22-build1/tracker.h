#pragma once

#include "shared.h"

// -- tracker defines --
// -- OMG !! DO NOT CHANGE THIS VALUE !! --
#define TRACKER_N_KEPT_UNSAFE_INTERACTION_DISTANCES 4

namespace track {


typedef enum {
    too_close    = 1,
    just_right   = 2,
    too_far      = 3,
    out_of_range = 4,
} status_t;


char* status_to_string(status_t stat);


typedef struct {
    /* -- state -- */
    status_t status;
    inches_t closest;
    bool entered_unsafe;
    bool in_interaction;
    /* -- over all time -- */
    uint8_t total_event_count;
    uint8_t unsafe_event_count;
    inches_t closest_events[TRACKER_N_KEPT_UNSAFE_INTERACTION_DISTANCES];
} tracker_t;

void init(tracker_t* tracker);

/// @brief send a new distance reading to the tracker
/// @param tracker the tracker to update (pointer)
/// @param new_dist the new, raw distance reading
/// @return the smoothed distance
inches_t new_dist(tracker_t* tracker, inches_t dist);

}  // namespace track
