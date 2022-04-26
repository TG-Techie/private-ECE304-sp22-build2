
#include "shared.h"

#pragma once  // include guard

// TODO(jay) add track functionality back to this
// #include "tracker.h"

void oled__init();

// void oled__update(track__tracker_t* tracker);


void oled__refresh(int total_count, int unsafe_count, inches_t* distances, int len);
