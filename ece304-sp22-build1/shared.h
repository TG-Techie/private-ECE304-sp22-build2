
#pragma once  // include guard

// a shared place for customizable values and datatypes used in the project


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


/* ------------------------------ debug / feature flags ------------------------------ */
/*  values for the on/off flags below */
#define OFF 0
#define ON  1

/* debug */
#define Serial_debug           OFF  // on/off, print debug messages to serial
#define Serial_debug_flush     ON  // on/off, wait for the transmission to finish before continuing
#define oled_delay_enable      OFF  // on/off, insert delays in oled code to help with debugging
#define oled_delay_duration_ms 100  // ms, duration of the delay in milliseconds

/* features */
#define SEVEN_SEG ON  // on/off,
#define LEDS      ON  // on/off,
#define SMOOTHING ON  // on/off,
#define OLED      ON  // on/off,
#define POWER     ON  // on/off,

#define LOOP_ITEATIONS_BETWEEN_SONAR_READS 2  // whole number,

#define FORCE_OLED_REFRESH OFF  // on/off,


/* ------------------------------------- config ------------------------------------- */

#define LOOP_ITEATIONS_BETWEEN_SONAR_READS 2  // number of loop iterations

/* -- thresholds defines -- */
#define JUST_RIGHT_THRESHOLD   (inches_t)(5 * 12)  // inches
#define TOO_FAR_THRESHOLD      (inches_t)(7 * 12)  // inches
#define OUT_OF_RANGE_THRESHOLD (inches_t)(9 * 12)  // inches

/* -- tracker defines -- */
#define TRACKER_MAX_EVENT_COUNT   4  // whole number, number of events to track
#define TRACKER_N_ROLLING_SAMPLES 4  // whole number, number of samples to average

/* -- smoothing defines -- */
#define N_SMOOTHING_SAMPLES 8  // whole number, number of samples to average

/* ----------------------------------- data types ----------------------------------- */
typedef float inches_t;
/* -- useful distance constants -- */
#define LARGE_DIST   (inches_t)(250 * 12)  // huge numer of inches
#define INVALID_DIST (inches_t)(0x00)      // 0 inches, ~0 feet (should not not be read)
// this is used as a marker to represent an empty distance, ie unset in a list
#define TOMBSTONE_DIST (inches_t)(0xDEAD * 12)  // huge numer of inches


/* --------------------------------- validity checks --------------------------------- */

/* check for oled and serial, because they do not mix well */
#if OLED && Serial_debug
#    error "OLED and Serial_debug cannot be enabled at the same time"
#endif

/* make they do get refreshed! */
#if LOOP_ITEATIONS_BETWEEN_SONAR_READS <= 0
#    error "LOOP_ITEATIONS_BETWEEN_SONAR_READS must be positive"
#endif

/* check that the smoother has some number of samples */
#if SMOOTHING && (N_SMOOTHING_SAMPLES <= 0)
#    error "N_SMOOTHING_SAMPLES must be positive"
#endif

/* --------------------------------- implementations --------------------------------- */

#if Serial_debug == 1
#    include "HardwareSerial.h"
#    define debug_print(val)                                                          \
        if (1) {                                                                      \
            Serial.print(val);                                                        \
            if (Serial_debug_flush) Serial.flush(); /* wait for transmission to end*/ \
        }

#    define debug_println(val)                                                        \
        if (1) {                                                                      \
            Serial.println(val);                                                      \
            if (Serial_debug_flush) Serial.flush(); /* wait for transmission to end*/ \
        }
#else
#    define debug_print(val)          \
        if (0) { /*debug_print(val)*/ \
        }
#    define debug_println(val)          \
        if (0) { /*debug_println(val)*/ \
        }
#endif


#if oled_delay_enable == 1
#    define oled_delay(msg)                \
        {                                  \
            debug_println(msg);            \
            delay(oled_delay_duration_ms); \
        }
#else
#    define oled_delay(msg)       \
        if (0) { /*oled_delay()*/ \
        }
#endif

#define INDENT_PP_DIRECTIVES 1