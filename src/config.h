#pragma once  // only include this header file once

#define OFF 0
#define ON  1

// --- feature flags ---
#define ENABLE_LEDS     ON
#define ENABLE_SEVENSEG ON
#define ENABLE_OLED     ON
#define ENABLE_POWER    OFF


// --- loop variables ---

#define REFRESH_DELAY                    5  // delay in ms for seven_seg refresh
#define LOOP_SONAR_REFRESH_EVERY_N_LOOPS 10

// --- tracker variables ---
#define JUST_RIGHT_THRESHOLD   (inches_t)(5 * 12)  // inches
#define TOO_FAR_THRESHOLD      (inches_t)(7 * 12)  // inches
#define OUT_OF_RANGE_THRESHOLD (inches_t)(9 * 12)  // inches
