
#pragma once  // include guard

#include "shared.h"

/// @brief Initialize the sonar sensor
/// @usage: `if (reading == INVALID_SONAR_READ) { <handle error> }`
#define INVALID_SONAR_READ -1

/// @brief related sonar fuctions

/// @brief Initialize the sonar sensor
void sonar__init();

/// @brief Read the sonar sensor
inches_t sonar__read();
