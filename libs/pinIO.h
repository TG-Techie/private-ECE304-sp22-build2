/*
MIT License

Copyright (c) 2022 Jonah "Jay" Y-M

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file pinIO.h
 * @brief Portable Pin IO functions to make gpio manupulation clearer.
 * @note Compile with AT LEAST `-O1` optimization on as this library produces dead code intended
 * to be optimized away
 * @author Jonah "Jay" Y-M (@TG-Techie)
 * @version 1.0
 * @date 2020-02-24
 */

#pragma once


typedef enum {
    INPUT  = 0,
    OUTPUT = 1,
} iodir_t;

typedef enum {
    LOW  = 0,
    HIGH = 1,
} ioval_t;


// --- declarations and arguement packing ---

// #define _expand_into(name, ...) name(__VA_ARGS__)

/**
 * @brief
 *
 */
#define pinIO_pin(port_letter, offset) port_letter, (1 << offset), offset, 1

/**
 * @brief
 *
 */
#define pinIO_range(port_letter, msbno, lsbno) \
    port_letter, (((1 << (msbno + 1)) - 1) >> lsbno), lsbno, (msbno - lsnno + 1)

/**
 * @brief
 *
 */
#define pinIO_offset(pin_pack) _pinIOoffset(pin_pack)

/**
 * @brief
 *
 */
#define pinIO_pinmask(pin_pack) _pinIOpinmask(pin_pack)

/**
 * @brief
 *
 */
#define pinIO_portchar(pin_pack) _pinIOportchar(pin_pack)

/**
 * @brief
 *
 */
#define pinIO_width(pin_pack) _pinIOwidth(pin_pack)

/**
 * @brief
 * @param pin_pack {some PinPack} the pin or range to set the direction of
 * @param dir {IODir_t} the direction to set the pin or range to
 */
#define setDir(pin_pack, dir) _pinIOsetDir(pin_pack, dir)


/**
 * @brief
 *
 */
#define setOut(pin_pack, value) _pinIOsetOut(pin_pack, value)

/**
 * @brief
 *
 */
#define getIn(pin_pack) _pinIOgetIn(pin_pack)

// --- impllmentations / unpack-macros ---

#define _pinIOoffset(port_letter, pinmask, offset, width) ((uint)offset)

#define _pinIOpinmask(port_letter, pinmask, offset, width) ((uint)pinmask)

#define _pinIOportchar(port_letter, pinmask, offset, width) ((char)(#port_letter[0]))

#define _pinIOwidth(port_letter, pinmask, offset, width) ((uint)width)

#define _pinIOsetDir(port_letter, pinmask, offset, width, dir) \
    if (dir == 1) {                                            \
        DDR##port_letter |= pinmask;                           \
    } else {                                                   \
        DDR##port_letter &= ~pinmask;                          \
    }

#define _pinIOsetOut(port_letter, pinmask, offset, width, value)                            \
    do {                                                                                    \
        PORT##port_letter = (PORT##port_letter & ~pinmask) + ((value << offset) & pinmask); \
    } while (0)

#define _pinIOgetIn(port_letter, pinmask, offset, width) \
    ((uint8_t)((PIN##port_letter & pinmask) >> offset))


#include <avr/io.h>


// FUTURE: with -O3 optimization
// #define irl(pin_pack) _irl(pin_pack)
// #define _irl(port_letter, mask, baseoffset, bitswidth) \
//     { \
//         .portaddr = (&PORT##port_letter), \
//         .pinmask = (mask), \
//         .offset = (baseoffset), \
//         .width = (bitswidth), \
//     }

// typedef struct {
//     volatile uint8_t* const portaddr;
//     uint const pinmask;
//     int const offset;
//     int const width;
// } PinPack;
// #define PinPack static const PinPack

// PinPack someport = irl(pinIO_range(D, 6, 0));

// #define setDir(pinpack, dir) \
//    if (dir == 1) {                                            \
//         *pinpack.portaddr |= pinpack.pinmask;                           \
//     } else {                                                   \
//         *pinpack.portaddr &= ~pinpack.pinmask;                          \
//     }
