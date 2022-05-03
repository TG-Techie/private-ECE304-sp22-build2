// interface
#include "sevenseg.h"
#include "config.h"
#include "board.h"


/* Illuminate 3 digits of the 4 digit 7 segment display
 * The 7 segments (a, b, c, d, e, f, g) correspond to ATmega328P pins D0-D7,
 * Arduino Uno pins 0-6. Enable pins DIG2, DIG3, DIG4 corresspond to PB0, PB1,
 * PB0, which correspondsd to Arduino Uno pins 8, 9, 10 */
#include "avr/io.h"
#include "util/delay.h"

// #define DIG2 PB2  // enables DIG2. ATmega328P pin PB2/Arduino Uno pin 10
// #define DIG3 PB1  // enables DIG3. ATmega328P pin PB1/Arduino Uno pin 9
// #define DIG4 PB0  // enables DIG4. ATmega328P pin PB0/Arduino Uno pin 8


// -- prototypes --
void disp_dist(uint8_t in);
void disp_none();

// -- global stored display state --
inches_t _num_to_show = 0;
bool _show_num        = false;

void se__init() {
#if ENABLE_SEVENSEG == ON
    setDir(sevenSegPort, OUTPUT);
    setDir(digEnPort, OUTPUT);
#endif
}

void disp3Digits(uint8_t ft, uint8_t in_tens, uint8_t in_ones) {
    static const uint8_t ledDigits[] = {
        0b00111111,  // 0
        0b00000110,  // 1
        0b01011011,  // 2
        0b01001111,  // 3
        0b01100110,  // 4
        0b01101101,  // 5
        0b01111101,  // 6
        0b00000111,  // 7
        0b01111111,  // 8
        0b01100111,  // 9
    };

    for (uint8_t i = 0; i < 5; i++) {
        // this code will refresh at 5 * REFRESH_DELAY us

        setOut(sevenSegPort, ledDigits[ft]);  // feet digit
        setOut(digEnPort, ~(1 << 2));         // Yes, they are flipped
        _delay_us(SEVENSEG_REFRESH_DELAY);
        setOut(digEnPort, 0x7);


        setOut(sevenSegPort, ledDigits[in_tens]);  // tens digit
        setOut(digEnPort, ~(1 << 1));
        _delay_us(SEVENSEG_REFRESH_DELAY);
        setOut(digEnPort, 0x7);

        setOut(sevenSegPort, ledDigits[in_ones]);  // ones digit
        setOut(digEnPort, ~(1 << 0));
        _delay_us(SEVENSEG_REFRESH_DELAY);
        setOut(digEnPort, 0x7);  // turn off all digits
    }
}

void disp_none() {
    setOut(sevenSegPort, 0x40);  // "-"

    for (uint8_t i = 0; i < 5; i++) {  // this code will refresh at 5*REFRESH_DELAY ms
        setOut(digEnPort, ~(1 << 2));
        _delay_us(SEVENSEG_REFRESH_DELAY);
        setOut(digEnPort, ~(1 << 0));
        _delay_us(SEVENSEG_REFRESH_DELAY);
        setOut(digEnPort, ~(1 << 0));
        _delay_us(SEVENSEG_REFRESH_DELAY);
        setOut(sevenSegPort, 0x40);
    }
}


void se__set_value(inches_t num) {
#if ENABLE_SEVENSEG == ON
    _show_num    = true;
    _num_to_show = num;
#endif
}

void se__set_value_none() {
#if ENABLE_SEVENSEG == ON
    _show_num = false;
#endif
}

void se__refresh() {
#if ENABLE_SEVENSEG == ON
    if (!_show_num)
        disp_none();
    else {
        uint8_t num = _num_to_show;
        disp3Digits(
            num / 12,       // feet
            num % 12 / 10,  // tens of inches
            num % 12 % 10   // ones of inches
        );
    }
#endif
}