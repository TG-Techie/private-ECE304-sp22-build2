# ECE304-Sp22-Build1

Pin assignments:

atmega328p pin #, what is in pin
1 -> programmer reset
2 -> seven seg A
3 -> seven seg B
4 -> seven seg C
5 -> seven seg D
6 -> seven seg E
7 -> VCC
8 -> GND
9 -> capacitor + 1 leg of 16MHz crystal
10 -> capacitor + 1 leg of 16MHz crystal
11 -> seven seg F
12 -> seven seg G
13 -> SONAR trig (change to 7 in Arduino code)
14 -> seven seg D4
15 -> seven seg D3
16 -> seven seg D1
17 -> programmer MOSI
18 -> programmer MISO
19 -> programmer SCK
20 -> empty
21 -> empty
22 -> empty
23 -> red LED (A0 in Arduino code)
24 -> green LED (A1 in Arduino code)
25 -> SONAR echo (change to A2 in Arduino code)
26 -> button (for power) (change to A3 in Arduino code)
27 -> SDA
28 -> SCL

Pins taken (atmega): 1, 7, 8, 9, 10, 17, 18, 19|

ATmega pin, Port number (arduino name) Description
Pin 1, PC6 (D0)
Pin 7, VCC
Pin 8, GND
Pin 9, PB6 () XTAL
Pin 10, PB7 () XTAL
Pin 17, PB3 (D11 / MOSI) Reserved for programming
Pin 18, PB4 (D12 / MISO) Reserved for programming
Pin 19, PB5 (D13 / SCK) Reserved for programming
pb2, pb1, pb0

(D10) One's place on seven seg
(D9) left most seven seg digit
(D8) 10's place on seven seg
#####ignore all this por favor ############

in order of abcdefgdp:

(D0-D7), PD0-PD7 pins (2-6, 11, 12, 13)
switch:

Pin 25, PC2, (A2)
OLED:

Pin 27, PC4, (SDA)
Pin 28, PC5, (SCL)
SONAR:

Pin 26, PC3, (A3) = echo
Pin 13, PD7, (7) = trigger
Power button:

Pin 2 on ATMega

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
