#pragma once  // include guard

#include "shared.h"
#include "tracker.h"

/** @brief Initialize the leds.
 *
 * basically just set the pin modes and turn them off
 */
void leds__init();

void leds__setstatus_from(track__status_t status);

void leds__off();

void leds__green();

void leds__red();

void leds__both();
