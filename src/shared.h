#pragma once  // only include this header file once

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


#include "i2c.h"

typedef float inches_t;

// do thing with these for now but leave them in
#define debug_print(...)
#define debug_println(...)