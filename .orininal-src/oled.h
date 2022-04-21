#pragma once  // include guard

#include "shared.h"
#include "tracker.h"

namespace oled {
void init();

void update(track__tracker_t* tracker);


// void refresh(int total_count, int unsafe_count, inches_t* distances, int len);

}  // namespace oled
