
#pragma once  // include guard

#include "shared.h"

namespace seven_seg {

typedef enum {
    none,
} none_t;

void init();

void refresh();
void set_value(inches_t);
void set_value(none_t);

}  // namespace seven_seg
