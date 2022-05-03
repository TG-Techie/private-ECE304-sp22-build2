
#pragma once  // include guard

#include "shared.h"


typedef enum {
    none,
} se__none_t;

void se__init();

void se__refresh();
void se__set_value(inches_t);
void se__set_value_none();
