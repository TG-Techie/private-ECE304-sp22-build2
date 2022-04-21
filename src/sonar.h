
#pragma once  // include guard

#include "shared.h"

/// @brief Initialize the sonar sensor
/// @usage: `if (reading == INVALID_SONAR_READ) { <handle error> }`
#define INVALID_SONAR_READ -1

/// @brief related sonar fuctions
namespace sonar {

/// @brief Initialize the sonar sensor
void init();

/// @brief Read the sonar sensor
float read();

float read_raw_cm();


}  // namespace sonar
