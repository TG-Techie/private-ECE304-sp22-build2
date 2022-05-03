#include "pinIO.h"

// PORTD reserves 0-6 for the seven segment
#define sevenSegPort pinIO_range(D, 6, 0)
#define echoPin      pinIO_pin(D, 7)
#define trigPin      pinIO_pin(B, 0)

#define dig0En    pinIO_pin(C, 0)
#define dig1En    pinIO_pin(C, 1)
#define dig3En    pinIO_pin(C, 2)
#define digEnPort pinIO_range(C, 2, 0)
