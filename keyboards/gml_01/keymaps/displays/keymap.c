/* Copyright 2020 Sergey Vlasov <sigprof@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "i2c_master.h"

static bool scrolling_mode = false;

#define DEFAULT_CPI 8000
#define SCROLLING_CPI 800

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[0] = LAYOUT(
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
  MO(3)  , KC_LCTL, KC_LALT, KC_LGUI, MO(1),   KC_SPC,  KC_SPC,  MO(2),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[1] = LAYOUT(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DELETE,
  KC_DEL,  KC_F1,   KC_MS_BTN3,   KC_MS_BTN2,   KC_MS_BTN1,   KC_F5,    KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12 , KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, _______,
  _______, _______, _______, _______, _______, _______,  _______, _______, KC_HOME, KC_PGDOWN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[2] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Fn
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  | Left |  Up  | Down |Right | Home | End  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[3] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, KC_HOME, KC_END,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

};



// #include "ch.h"
// #include "hal.h"
// #include <string.h>


#define ALPHANUM_ADDRESS (0x70 << 1)
#define MATRIX_ADDRESS (0x71 << 1)

// TODO assume timeout in ms?
#define ALPHANUM_TIMEOUT 50

#define ALPHANUM_DEFAULT_BRIGHTNESS 4
#define ALPHANUM_MAX_BRIGHTNESS 15
#define ALPHANUM_MIN_BRIGHTNESS 0

#define HT16K33_BLINK_CMD 0x80       ///< I2C register for BLINK setting
#define HT16K33_BLINK_DISPLAYON 0x01 ///< I2C value for steady on
#define HT16K33_BLINK_OFF 0          ///< I2C value for steady off
#define HT16K33_BLINK_2HZ 1          ///< I2C value for 2 Hz blink
#define HT16K33_BLINK_1HZ 2          ///< I2C value for 1 Hz blink
#define HT16K33_BLINK_HALFHZ 3       ///< I2C value for 0.5 Hz blink

#define HT16K33_CMD_BRIGHTNESS 0xE0 ///< I2C register for BRIGHTNESS setting
#define HT16K33_OSC_ON 0x21

static uint8_t i2c_data[20];

static uint16_t alpha_display_buffer[8]; ///< Raw display data
static uint16_t matrix_display_buffer[8]; ///< Raw display data

static uint8_t brightness = ALPHANUM_DEFAULT_BRIGHTNESS;

static const uint16_t alphafonttable[] PROGMEM = {

    0b0000000000000001, 0b0000000000000010, 0b0000000000000100,
    0b0000000000001000, 0b0000000000010000, 0b0000000000100000,
    0b0000000001000000, 0b0000000010000000, 0b0000000100000000,
    0b0000001000000000, 0b0000010000000000, 0b0000100000000000,
    0b0001000000000000, 0b0010000000000000, 0b0100000000000000,
    0b1000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0001001011001001, 0b0001010111000000, 0b0001001011111001,
    0b0000000011100011, 0b0000010100110000, 0b0001001011001000,
    0b0011101000000000, 0b0001011100000000,
    0b0000000000000000, //
    0b0000000000000110, // !
    0b0000001000100000, // "
    0b0001001011001110, // #
    0b0001001011101101, // $
    0b0000110000100100, // %
    0b0010001101011101, // &
    0b0000010000000000, // '
    0b0010010000000000, // (
    0b0000100100000000, // )
    0b0011111111000000, // *
    0b0001001011000000, // +
    0b0000100000000000, // ,
    0b0000000011000000, // -
    0b0000000000000000, // .
    0b0000110000000000, // /
    0b0000110000111111, // 0
    0b0000000000000110, // 1
    0b0000000011011011, // 2
    0b0000000010001111, // 3
    0b0000000011100110, // 4
    0b0010000001101001, // 5
    0b0000000011111101, // 6
    0b0000000000000111, // 7
    0b0000000011111111, // 8
    0b0000000011101111, // 9
    0b0001001000000000, // :
    0b0000101000000000, // ;
    0b0010010000000000, // <
    0b0000000011001000, // =
    0b0000100100000000, // >
    0b0001000010000011, // ?
    0b0000001010111011, // @
    0b0000000011110111, // A
    0b0001001010001111, // B
    0b0000000000111001, // C
    0b0001001000001111, // D
    0b0000000011111001, // E
    0b0000000001110001, // F
    0b0000000010111101, // G
    0b0000000011110110, // H
    0b0001001000000000, // I
    0b0000000000011110, // J
    0b0010010001110000, // K
    0b0000000000111000, // L
    0b0000010100110110, // M
    0b0010000100110110, // N
    0b0000000000111111, // O
    0b0000000011110011, // P
    0b0010000000111111, // Q
    0b0010000011110011, // R
    0b0000000011101101, // S
    0b0001001000000001, // T
    0b0000000000111110, // U
    0b0000110000110000, // V
    0b0010100000110110, // W
    0b0010110100000000, // X
    0b0001010100000000, // Y
    0b0000110000001001, // Z
    0b0000000000111001, // [
    0b0010000100000000, //
    0b0000000000001111, // ]
    0b0000110000000011, // ^
    0b0000000000001000, // _
    0b0000000100000000, // `
    0b0001000001011000, // a
    0b0010000001111000, // b
    0b0000000011011000, // c
    0b0000100010001110, // d
    0b0000100001011000, // e
    0b0000000001110001, // f
    0b0000010010001110, // g
    0b0001000001110000, // h
    0b0001000000000000, // i
    0b0000000000001110, // j
    0b0011011000000000, // k
    0b0000000000110000, // l
    0b0001000011010100, // m
    0b0001000001010000, // n
    0b0000000011011100, // o
    0b0000000101110000, // p
    0b0000010010000110, // q
    0b0000000001010000, // r
    0b0010000010001000, // s
    0b0000000001111000, // t
    0b0000000000011100, // u
    0b0010000000000100, // v
    0b0010100000010100, // w
    0b0010100011000000, // x
    0b0010000000001100, // y
    0b0000100001001000, // z
    0b0000100101001001, // {
    0b0001001000000000, // |
    0b0010010010001001, // }
    0b0000010100100000, // ~
    0b0011111111111111,
};

static void start(uint8_t address) {
  i2c_start(address);
}

static void write(uint8_t address, uint8_t a) {
  i2c_data[0] = a;
  i2c_transmit(address, i2c_data, 1, ALPHANUM_TIMEOUT);
}

static void stop(void) {
  i2c_stop();
}

static void set_brightness(uint8_t b) {
  if (b > 15)
    b = 15;
  start(ALPHANUM_ADDRESS);
  write(ALPHANUM_ADDRESS, HT16K33_CMD_BRIGHTNESS | b);
  stop();
  start(MATRIX_ADDRESS);
  write(MATRIX_ADDRESS, HT16K33_CMD_BRIGHTNESS | b);
  stop();
}

static void set_blink_rate(uint8_t b) {
  if (b > 3) b = 0; // turn off if not sure

  start(ALPHANUM_ADDRESS);
  write(ALPHANUM_ADDRESS, HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1));
  stop();

  start(MATRIX_ADDRESS);
  write(MATRIX_ADDRESS, HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1));
  stop();
}

static void write_display(uint8_t address, uint16_t *display_buffer) {

  // TODO Use one transfer?
  i2c_data[0] = 0x00; // start at address $00

  for (uint8_t i = 0; i < 8; i++) {
    i2c_data[1 + i * 2] = display_buffer[i] & 0xFF;
    i2c_data[1 + i * 2 + 1] = display_buffer[i] >> 8;
  }

    start(address);
  i2c_transmit(address, i2c_data, 1 + 8 * 2, ALPHANUM_TIMEOUT);
    stop();
}

static void write_digits(void) {
  write_display(ALPHANUM_ADDRESS, alpha_display_buffer);
}

static void write_matrix(void) {
  write_display(MATRIX_ADDRESS, matrix_display_buffer);
}

static void write_all(void) {
  write_digits();
  write_matrix();
}

static void write_digit_raw(uint8_t n, uint16_t bitmask) {
  alpha_display_buffer[n] = bitmask;
}

static void write_digit_ascii(uint8_t n, uint8_t a, bool d) {
  uint16_t font = pgm_read_word(alphafonttable + a);

  alpha_display_buffer[n] = font;

  if (d)
    alpha_display_buffer[n] |= (1 << 14);
}

#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  } ///< 16-bit var swap
#endif


static void draw_pixel(int16_t x, int16_t y, uint16_t color) {

  if ((y < 0) || (y >= 8))
    return;
  if ((x < 0) || (x >= 16))
    return;

  // Note for logic - with the wing arranged landscape, so that the USB connector
  // of the feather would be on the left (hence matching the silkscreen pin labels
  // at least on the feathers I've seen), we have a left panel and a right panel.
  // Viewed this way, the matrix_display_buffer is laid out oddly - each unit16_t
  // in the buffer runs along a pair of columns of the display, bit 0 is at the
  // bottom of the left panel, bit 1 is above it, and so on to bit 7 at the top
  // of the left panel, then bit 8 is at the bottom of the right panel, and so
  // on going up through the right panel. The first unit16_t covers the left
  // most column of each panel, then the next covers the one to the right, and
  // so on to the 7th unit16_t which covers the rightmost column of each panel.
  // This means that the layout doesn't have an easy transformation to a direct
  // mapping of any rotation of the display.
  // We choose a mapping starting in the top left, with x going right, and y going
  // down.

  // Convert to row and column
  int r;
  int c;

  // Left panel
  if (x < 8) {
    r = x;
    c = 7 - y;

  // Right panel
  } else {
    r = x - 8;
    c = 15 - y;
  }

  if (color) {
    matrix_display_buffer[r] |= 1 << c;
  } else {
    matrix_display_buffer[r] &= ~(1 << c);
  }
}

void clear(void) {
  for (uint8_t i = 0; i < 8; i++) {
    alpha_display_buffer[i] = 0;
    matrix_display_buffer[i] = 0;
  }
}

static void brighter(void) {
  if (brightness < ALPHANUM_MAX_BRIGHTNESS) {
    brightness++;
    set_brightness(brightness);
  }
}

static void dimmer(void) {
  if (brightness > ALPHANUM_MIN_BRIGHTNESS) {
    brightness--;
    set_brightness(brightness);
  }
}

static void display_init(void) {
  start(ALPHANUM_ADDRESS);
  write(ALPHANUM_ADDRESS, HT16K33_OSC_ON);
  stop();
  start(MATRIX_ADDRESS);
  write(MATRIX_ADDRESS, HT16K33_OSC_ON);
  stop();
}

void matrix_init_kb(void) {
  matrix_init_user();

  i2c_init();
  display_init();

  // Clear memory, may not be empty
  clear();
  write_digit_ascii(0, 'G', false);
  write_digit_ascii(1, 'm', false);
  write_digit_ascii(2, 'L', false);
  write_digit_ascii(3, '1', false);

  write_all();

  set_blink_rate(HT16K33_BLINK_OFF);
  set_brightness(ALPHANUM_DEFAULT_BRIGHTNESS);

}

// TODO move to gml01.c?
#if POINTING_DEVICE_ENABLE
void pointing_device_init_kb(void){
    pointing_device_init_user();

    pointing_device_set_cpi(DEFAULT_CPI);
}
#endif

static bool splash = true;

#define SPLASH_INTERVAL 100
#define SPLASH_MAX_PHASE 96
#define SPLASH_START_PHASE 16
static int splash_delay = 0;
static int splash_phase = 0;

void matrix_scan_user(void) {
  if (splash) {
    splash_delay++;
    if (splash_delay > SPLASH_INTERVAL) {
      splash_delay = 0;
      if (splash_phase < SPLASH_MAX_PHASE) {
        splash_phase++;
        for (int x = 0; x < 16; x++) {
          for (int y = 0; y < 8; y++) {
            int d = abs((x + y) - (splash_phase - 32));
            // int d = (x + y) - (splash_phase - 16);
            // bool on = d == 0 || d == -1 || d == -5;
            bool on = d < 3;
            draw_pixel(x, y, on);
          }
        }
        write_all();
      }
    }
  }
}

static int left_cols[] = { 1, 5, 4, 3, 0, 2 };
static int right_cols[] = { 0, 1, 4, 5, 3, 2 };


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

  bool process = true;

  process_record_user(keycode, record);

  if (splash) {
    clear();
    splash = false;
  }

  int x = record->event.key.col;
  int y = record->event.key.row;

  // Adapt for particular layout of rows and columns
  if (y <= 3) {
    x = left_cols[x];
  } else {
    y -= 4;
    x = right_cols[x] + 6;
  }

  draw_pixel(x + 2, y + 2, record->event.pressed);

  switch (keycode) {
    case KC_VOLU:
      if (record->event.pressed){
        brighter();
        write_digit_ascii(1, 'B', false);
        write_digit_ascii(2, '0' + brightness / 10, false);
        write_digit_ascii(3, '0' + brightness % 10, false);
        // write_digits();
      }
      process = true;
      break;

    case KC_VOLD:
      if (record->event.pressed) {
        dimmer();
        write_digit_ascii(1, 'B', false);
        write_digit_ascii(2, '0' + brightness / 10, false);
        write_digit_ascii(3, '0' + brightness % 10, false);
        // write_digits();
      }
      process = true;
      break;

    default:
      write_digit_ascii(1, 'G', false);
      write_digit_ascii(2, 'm', false);
      write_digit_ascii(3, 'L', false);
      // uint8_t wpm = get_current_wpm();
      // write_digit_ascii(1, '0' + wpm / 100, false);
      // write_digit_ascii(2, '0' + (wpm / 10) % 10, false);
      // write_digit_ascii(3, '0' + brightness % 10, false);
      // write_digits();
      process = true;  // Process all other keycodes normally
      break;
  }

  write_all();

  return process;
}

static int scroll_total_x = 0;
static int scroll_total_y = 0;

#define SCROLL_DIVISOR 16

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (scrolling_mode) {

        scroll_total_x += mouse_report.x;
        scroll_total_y += mouse_report.y;

        int scroll_x = scroll_total_x / SCROLL_DIVISOR;
        int scroll_y = scroll_total_y / SCROLL_DIVISOR;

        if (scroll_x != 0) {
            scroll_total_x -= scroll_x * SCROLL_DIVISOR;
        }
        if (scroll_y != 0) {
            scroll_total_y -= scroll_y * SCROLL_DIVISOR;
        }

        mouse_report.h = scroll_x;
        mouse_report.v = -scroll_y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        scroll_total_x = 0;
        scroll_total_y = 0;
    }
    return mouse_report;
}


layer_state_t layer_state_set_kb(layer_state_t state) {
  layer_state_set_user(state);

    if (!splash) {
        switch (get_highest_layer(state)) {
        case 1:
            write_digit_ascii(0, '_', false);
            break;
        case 2:
            write_digit_raw(0, 0b1);
            break;
        case 3:
            write_digit_ascii(0, '+', false);
            break;
        default:
            write_digit_ascii(0, '-', false);
        }
        write_digits();
    }

#if POINTING_DEVICE_ENABLE
    switch (get_highest_layer(state)) {
        case 3:  // If we're on the FN layer enable scrolling mode
            scrolling_mode = true;
            pointing_device_set_cpi(SCROLLING_CPI);
            break;
        default:
            if (scrolling_mode) {  // check if we were scrolling before and set disable if so
                scrolling_mode = false;
                pointing_device_set_cpi(DEFAULT_CPI);
            }
            break;
    }
#endif

  return state;
}


void matrix_scan_kb(void) {
  matrix_scan_user();
}

