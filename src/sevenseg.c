// interface
#include "sevenseg.h"
#include "config.h"

/* Illuminate 3 digits of the 4 digit 7 segment display
 * The 7 segments (a, b, c, d, e, f, g) correspond to ATmega328P pins D0-D7,
 * Arduino Uno pins 0-6. Enable pins DIG2, DIG3, DIG4 corresspond to PB0, PB1,
 * PB0, which correspondsd to Arduino Uno pins 8, 9, 10 */
#include "avr/io.h"
#include "util/delay.h"

#define DIG2          PB2  // enables DIG2. ATmega328P pin PB2/Arduino Uno pin 10
#define DIG3          PB1  // enables DIG3. ATmega328P pin PB1/Arduino Uno pin 9
#define DIG4          PB0  // enables DIG4. ATmega328P pin PB0/Arduino Uno pin 8
#define REFRESH_DELAY 5    // delay in ms for seven_seg refresh


// -- prototypes --
void disp_dist(uint8_t in);
void disp_none();

// -- global stored display state --
inches_t _num_to_show = 0;
bool _show_num        = false;

void ss__init() {
#if ENABLE_SEVENSEG == ON
    debug_print("seven_seg::init()... ");
    DDRD = 0xFF;                                   // 7segment pins
    DDRB = DDRB | (1 << 2) | (1 << 1) | (1 << 0);  // digit enables
    debug_println("done");
#endif
}


void ss__set_value(inches_t num) {
#if ENABLE_SEVENSEG == ON
    _show_num    = true;
    _num_to_show = num;
#endif
}

void ss__set_value_none() {
#if ENABLE_SEVENSEG == ON
    _show_num = false;
#endif
}

void ss__refresh() {
#if ENABLE_SEVENSEG == ON
    if (_show_num) {
        disp_dist(_num_to_show);
    } else {
        disp_none();
    }
#endif
}


void disp3Digits(unsigned char d1, unsigned char d2, unsigned char d3) {
    static const unsigned char ledDigits[] = {
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

    for (unsigned char i = 0; i < 5; i++) {  // this code will refresh at 5*REFRESH_DELAY ms

        PORTD = ledDigits[d1];              // feet digit
        PORTB = (1 << DIG3) | (1 << DIG4);  // enable DIG2, disable DIG3 & DIG4, 0000 0011
        _delay_ms(REFRESH_DELAY);


        PORTD = ledDigits[d2];              // first inches digit
        PORTB = (1 << DIG2) | (1 << DIG4);  // enable DIG3, disable DIG2,DIG4  0000 0101
        _delay_ms(REFRESH_DELAY);

        PORTD = ledDigits[d3];              // second inches digit
        PORTB = (1 << DIG2) | (1 << DIG3);  // enable DIG4, disable DIG2,DIG3 0000 0110
        _delay_ms(REFRESH_DELAY);
    }
    return;
}

void disp_dist(uint8_t all_in) {
    // Displays distance on the seven segment display, given inches (less than 10
    // ft) it displays feet and inches in correct format
    // unsigned char ft;   // distance in feet
    // unsigned char in1;  // first digit of inches
    // unsigned char in2;  // second digit of inches

    // calculate and display digits
    unsigned char ft  = all_in / 12;  // distance in feet
    unsigned char in  = all_in % 12;  // total value of inches without feet
    unsigned char in1 = in / 10;      // first digit of inches
    unsigned char in2 = in % 10;      // second digit of inches

    disp3Digits(in2, in1, ft);
}


void disp_none() {
    PORTD = 1 << 6;

    for (unsigned char i = 0; i < 5; i++) {  // this code will refresh at 5*REFRESH_DELAY ms
        PORTB = (1 << DIG3) | (1 << DIG4);
        _delay_ms(REFRESH_DELAY);
        PORTB = (1 << DIG2) | (1 << DIG4);
        _delay_ms(REFRESH_DELAY);
        PORTB = (1 << DIG2) | (1 << DIG3);
        _delay_ms(REFRESH_DELAY);
    }
}
