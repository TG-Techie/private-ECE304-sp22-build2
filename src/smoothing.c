
#include "smoothing.h"

#include "string.h"


void smooth__init(smooth__smoother_t* smoother) {
#if ENABLE_SMOOTHING == OFF
    smoother->samples[0] = 0;
#else
    smoother->sample_dest = 0;
    memset(smoother->samples, 0, sizeof(smoother->samples));
#endif
}

void smooth__insert(smooth__smoother_t* smoother, inches_t new_sample) {
#if ENABLE_SMOOTHING == OFF
    smoother->samples[0] = new_sample;
#else
    if (new_sample == 0) return;  // skip zero values

    smoother->samples[smoother->sample_dest] = new_sample;

    smoother->sample_dest = (smoother->sample_dest + 1) % N_SMOOTHING_SAMPLES;

#endif
}

inches_t smooth__get_smoothed(smooth__smoother_t* smoother) {
#if ENABLE_SMOOTHING == OFF
    return smoother->samples[0];
#else
    inches_t highest      = -1;
    inches_t lowest       = LARGE_DIST;  // a stupid hihg number of feet
    inches_t sum          = 0;
    for (int i = 0; i < N_SMOOTHING_SAMPLES; i++) {
        inches_t sample = smoother->samples[i];
        if (sample > highest) highest = sample;
        if (sample < lowest) lowest = sample;
        sum += sample;
    }
    return (sum - highest - lowest) / (N_SMOOTHING_SAMPLES - 2);
#endif
}
