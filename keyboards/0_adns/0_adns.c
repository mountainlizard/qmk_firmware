#include "0_adns.h"

#include "ch.h"
#include "hal.h"

void matrix_init_kb(void) {
	matrix_init_user();

	// i2c_init(); 
	// display_init();

	// // Clear memory, may not be empty
	// clear();
	// write_digit_ascii(0, 'G', false);
	// write_digit_ascii(1, 'm', false);
	// write_digit_ascii(2, 'L', false);
	// write_digit_ascii(3, '1', false);

	// write_all();

	// set_blink_rate(HT16K33_BLINK_OFF);
	// set_brightness(ALPHANUM_DEFAULT_BRIGHTNESS);
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}