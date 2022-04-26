# ECE304-Sp22-Build1

Pins taken (atmega): 1, 7, 8, 9, 10, 17, 18, 19|

- ATmega pin, Port number (arduino name) Description
- Pin 1, PC6 (D0)
- Pin 7, VCC
- Pin 8, GND
- Pin 9, PB6 () XTAL
- Pin 10, PB7 () XTAL
- Pin 17, PB3 (D11 / MOSI) Reserved for programming
- Pin 18, PB4 (D12 / MISO) Reserved for programming
- Pin 19, PB5 (D13 / SCK) Reserved for programming

pb2, pb1, pb0

- (D10) One's place on seven seg
- (D9) left most seven seg digit
- (D8) 10's place on seven seg

switch:

- Pin 25, PC2, (A2)

OLED:

- Pin 27, PC4, (SDA)
- Pin 28, PC5, (SCL)

# Code changes:

#### TODO / critical:

- [ ] re-download stock files b/c Jonah editted some.many of them (makefile, oled, sevenseg, etc)
- [ ] de-comment then re-comment the codes
- [ ] change pin assignments
- [ ] de modularize / parameterize the code
- [ ] re-write trackker / smoother code
  - the tracker can have different thresholds and behaviors
- [ ] remove listed jonah-isms below

#### Jonah-ey things to remove:

- [ ] fix jonah for loops and do while loops instead
- [ ] pragma to ifndef
- [ ] de-typedef stuff, ie no inches_t, uint8_t, bool, etc

#### misc ideas

- all different trackers and names
- module names / remove modules all together
- structs into global variables
- LED configuration/function names (maybe no functions)
- undo clang format manually/make different clang format for another one
- demodularize it (less files), de-parameterize it (no shared.h and shared.c)
- use mclaughlin's makefile instead of currently modified one
- (Jonah will) move the provided code into a separate folder
- (Jonah will) add the other promised fucntionality he has on pdr
