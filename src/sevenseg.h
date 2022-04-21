
#pragma once  // include guard

#include "shared.h"


typedef enum {
    none,
} ss__none_t;

void ss__init();

void ss__refresh();
void ss__set_value(inches_t);
void ss__set_value_none();
