#pragma once  // only include this header file once

#define OFF 0
#define ON  1

// --- feature flags ---
#define ENABLE_LEDS     ON
#define ENABLE_SEVENSEG ON
#define ENABLE_OLED     ON


// --- loop variables ---
#define LOOP_DELAY_MS                    10
#define LOOP_SONAR_REFRESH_EVERY_N_LOOPS 10

// --- tracker variables ---
#define JUST_RIGHT_THRESHOLD   (inches_t)(5 * 12)  // inches
#define TOO_FAR_THRESHOLD      (inches_t)(7 * 12)  // inches
#define OUT_OF_RANGE_THRESHOLD (inches_t)(9 * 12)  // inches

typedef float inches_t;
/* -- useful distance constants -- */
#define LARGE_DIST   (inches_t)(250 * 12)  // huge numer of inches
#define INVALID_DIST (inches_t)(0x00)      // 0 inches, ~0 feet (should not not be read)
// this is used as a marker to represent an empty distance, ie unset in a list
#define TOMBSTONE_DIST (inches_t)(0xDEAD * 12)  // huge numer of inches
