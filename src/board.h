#include "pinIO.h"

// --- seven segment ---
// PORTD reserves 0-6 for the seven segment
#define sevenSegPort pinIO_range(D, 6, 0)

#define digEnPort pinIO_range(C, 2, 0)

// --- sonar ---
#define echoPin pinIO_pin(B, 0)
#define trigPin pinIO_pin(D, 7)

// --- leds ---
#define greenLedPin pinIO_pin(B, 1)  // how did copilot predict these twp pins !?
#define redLedPin   pinIO_pin(B, 2)