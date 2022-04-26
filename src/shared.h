#pragma once  // only include this header file once

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


#include "i2c.h"

typedef float inches_t;

/* -- useful distance constants -- */
#define LARGE_DIST   (inches_t)(250 * 12)  // huge numer of inches
#define INVALID_DIST (inches_t)(0x00)      // 0 inches, ~0 feet (should not not be read)
// this is used as a marker to represent an empty distance, ie unset in a list
#define TOMBSTONE_DIST (inches_t)(0xDEAD * 12)  // huge numer of inches


// do thing with these for now but leave them in
#define debug_print(...)
#define debug_println(...)