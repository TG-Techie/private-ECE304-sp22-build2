
#pragma once

#include "shared.h"

namespace smooth {

/** @brief Initialize the smoother.
 *
 * Wrap kaz's algorithm in a struct to make it easier to manage.
 */
typedef struct {
    int sample_dest;
    inches_t samples[N_SMOOTHING_SAMPLES];
} smoother_t;

/** @brief Initialize the smoother.
 *
 * @param smoother the smoother to initialize
 * @return void
 *
 * this function is called by the constructor of the smoother_t struct, is fills the struct with
 * default values (zeros) and sets the sample_dest to 0.
 */
void init(smoother_t* smoother);

/** @brief Insert a new sample into the smoother.
 *
 * @param smoother the smoother to update
 * @param new_sample the new sample to insert
 * @return void
 *
 * this function serts the new sample into the smoother replacing the oldest sample.
 * skips zero values.
 */
void insert(smoother_t* smoother, inches_t new_sample);

/** @brief get the smoothed distance
 *  @param smoother the smoother to use
 *  @return the smoothed distance
 *
 * This currently uses an algorithm that drops the lowest and highest samples
 */
inches_t get_smoothed(smoother_t* smoother);


}  // namespace smooth