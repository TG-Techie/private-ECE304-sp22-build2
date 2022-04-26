
#include "smoothing.h"

#include "string.h"

namespace smooth {

void init(smoother_t* smoother) {
    debug_println("smooth::init()... ");
    smoother->sample_dest = 0;
    memset(smoother->samples, 0, sizeof(smoother->samples));
    debug_println("done");
}

void insert(smoother_t* smoother, inches_t new_sample) {
    if (new_sample == 0) return;

    smoother->samples[smoother->sample_dest] = new_sample;

    smoother->sample_dest = (smoother->sample_dest + 1) % N_SMOOTHING_SAMPLES;
}

inches_t get_smoothed(smoother_t* smoother) {
    inches_t highest = -1;
    inches_t lowest  = LARGE_DIST;  // a stupid hihg number of feet
    inches_t sum     = 0;
    for (int i = 0; i < N_SMOOTHING_SAMPLES; i++) {
        inches_t sample = smoother->samples[i];
        if (sample > highest) highest = sample;
        if (sample < lowest) lowest = sample;
        sum += sample;
    }
    return (sum - highest - lowest) / (N_SMOOTHING_SAMPLES - 2);
}

}  // namespace smooth