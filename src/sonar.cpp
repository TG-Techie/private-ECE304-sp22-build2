
// interface
#include "sonar.h"


void sonar__init() {
    // HCSR05
    // https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf#page=53
    // This uses arduino A5 as the input thus
}


float sonar__read() {
    double cm     = hc.dist();
    double inches = cm / 2.54;
    return inches;
}
