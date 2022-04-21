#pragma once  // include guard

#include "shared.h"

namespace leds {
/** @brief Initialize the leds.
 *
 * basically just set the pin modes and turn them off
 */
void init();

void off();

void green();

void red();

void both();

}  // namespace leds
