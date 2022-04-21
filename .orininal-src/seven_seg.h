
#pragma once  // include guard

#include "shared.h"

namespace seven__seg {

typedef enum {
    none,
} ss_none_t;

void ss_init();

void ss_refresh();
void ss_set_value(inches_t);
void ss_set_value(none_t);

}  // namespace seven__seg
