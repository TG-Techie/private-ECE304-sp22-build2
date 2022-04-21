#pragma once  // include guard

#include "shared.h"

/** @brief Initialize the leds.
 *
 * basically just set the pin modes and turn them off
 */
void leds__init();

void leds__off();

void leds__green();

void leds__red();

void leds__both();
