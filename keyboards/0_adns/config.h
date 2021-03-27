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
#define PRODUCT GML1
#define DESCRIPTION Great Mountain Lizard 1


/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { B9, C3, C2, C1, B8, C6, C7, B11 }
#define MATRIX_COL_PINS { A4, A5, A6, A7, C4, C5 }

#define DIODE_DIRECTION COL2ROW

// The bank of pins (GPIOA, GPIOB, GPIOC) to use for SCL
#define I2C1_SCL_BANK GPIOB

// The bank of pins (GPIOA, GPIOB, GPIOC) to use for SDA
#define I2C1_SDA_BANK GPIOB

// The pin number for the SCL pin (0-15)
#define I2C1_SCL 6

// The pin number for the SCL pin (0-15)
#define I2C1_SDA 7
