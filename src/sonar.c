
// interface
#include "sonar.h"
#include "config.h"

void sonar__init() {
#if ENABLE_SONAR == ON
    // HCSR05
    // https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf#page=53
    // This uses arduino A3 as the input ie PC3 on pin 17
    {}
#endif
}


inches_t sonar__read() {
#if ENABLE_SONAR == ON
    return INVALID_DIST;
#endif
}
