/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
/* in python2: list(u"whatever".encode('utf-16-le')) */
/*   at most 32 characters or the ugly hack in usb_main.c borks */
#define MANUFACTURER QMK
#define PRODUCT AFE405
#define DESCRIPTION AdaFruit Feather Express F405

// /* key matrix size */
// #define MATRIX_ROWS 4
// #define MATRIX_COLS 4

// #define MATRIX_COL_PINS { B7, B8, B9, B10 }
// #define MATRIX_ROW_PINS { B3, B4, B5, B6 }
// #define DIODE_DIRECTION COL2ROW

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 1

/* Direct connections on silkscreen Ao (which is MCU A4) and silkscreen A1 (which is MCU A5)*/
#define DIRECT_PINS { \
    {A4}, \
    {A5} \
}

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

