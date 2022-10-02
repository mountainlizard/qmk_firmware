// Copyright 2022 Ben Webster (@trepidacious)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/*
#define MATRIX_COL_PINS \
    { GP4 }
#define MATRIX_ROW_PINS \
    { GP5 }
*/

#define DEBUG_MATRIX_SCAN_RATE

#define QMK_WAITING_TEST_BUSY_PIN GP8
#define QMK_WAITING_TEST_YIELD_PIN GP9

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define RGB_DI_PIN A1

// OLED on pins GP16 and GP17 (standard Pico labelling)
// #define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5

// SPI and Trackball settings
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
// MISO should be 16, but we're using this for D/C on LCD panel so just assign another unused MISO pin, GP0 is SPI0RX and is not connected to anything on breakout garden, we're not using UART0 so should be fine
#define SPI_MISO_PIN GP0
// #define ADNS9800_CS_PIN GP17
// #define POINTING_DEVICE_INVERT_X
// #define POINTING_DEVICE_TASK_THROTTLE_MS 1

// #define MOUSE_EXTENDED_REPORT
// #define PIMORONI_TRACKBALL_ADDRESS 0x0A
// #define PIMORONI_TRACKBALL_SCALE 1
// #define POINTING_DEVICE_TASK_THROTTLE_MS 1


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
