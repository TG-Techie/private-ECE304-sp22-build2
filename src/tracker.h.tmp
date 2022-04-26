#pragma once

#include "shared.h"

// -- tracker defines --
// -- OMG !! DO NOT CHANGE THIS VALUE !! --
#define TRACKER_N_KEPT_UNSAFE_INTERACTION_DISTANCES 4

typedef enum {
    too_close    = 1,
    just_right   = 2,
    too_far      = 3,
    out_of_range = 4,
} track__status_t;

char* track__status_to_string(track__status_t stat);


typedef struct {
    /* -- state -- */
    track__status_t status;
    inches_t closest;
    bool entered_unsafe;
    bool in_interaction;
    /* -- over all time -- */
    uint8_t total_event_count;
    uint8_t unsafe_event_count;
    inches_t closest_events[TRACKER_N_KEPT_UNSAFE_INTERACTION_DISTANCES];
} track__tracker_t;

void track__init(track__tracker_t** tracker);

/// @brief send a new distance reading to the tracker
/// @param tracker the tracker to update (pointer)
/// @param track__new_dist the new, raw distance reading
/// @return the smoothed distance
inches_t track__new_dist(track__tracker_t* tracker, inches_t dist);
