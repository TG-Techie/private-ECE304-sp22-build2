#pragma once  // only include this header file once

#define OFF 0
#define ON  1

// --- feature flags ---
#define ENABLE_LEDS      ON
#define ENABLE_SEVENSEG  ON
#define ENABLE_OLED      OFF
#define ENABLE_POWER     OFF
#define ENABLE_SMOOTHING ON
#define ENABLE_TRACKING  ON

// --- smooth variables ---
#define N_SMOOTHING_SAMPLES 3

// --- loop variables ---
#define FORCE_OLED_REFRESH               OFF  // on/off
#define LOOP_SONAR_REFRESH_EVERY_N_LOOPS 15

// --- seven segment ---
#define SEVENSEG_REFRESH_DELAY       100  // delay in ms for seven_seg refresh
#define SEVENSEG_REPEATS_PER_REFRESH 5

// --- tracker variables ---
#define JUST_RIGHT_THRESHOLD   (inches_t)(5 * 12)       // inches
#define TOO_FAR_THRESHOLD      (inches_t)(7 * 12)       // inches
#define OUT_OF_RANGE_THRESHOLD (inches_t)(9 * 12 + 11)  // inches
