#include <string.h>
#include "quantum.h"
#include "color.h"

#include <hal_pal.h>
#include "qp.h"
#include "generated/lcd240.qgf.h"
#include "generated/gml240.qgf.h"
#include "generated/lower240.qgf.h"

painter_device_t lcd;
static painter_image_handle_t lcd240;
static painter_image_handle_t gml240;
static painter_image_handle_t lower240;

#define HSV_GML_GOLD    33, 198, 255

//----------------------------------------------------------
// Initialisation

// This is normally MISO, but on breakout garden is connected to DC
#define LCD_DC_PIN GP16
// #define LCD_DC_PIN NO_PIN
// CE1 on breakout garden, for "front" SPI, labelled A on PCB
#define LCD_CS_PIN GP17
// If NO_PIN doesn't work, we could use GP26, which is not connected to anything on pico breakout garden
#define LCD_RST_PIN NO_PIN
// This is PWM1 on breakout garden, which is connected to BL on LCD
#define LCD_BL_PIN GP20
#define LCD_SPI_DIVISOR 1
#define LCD_SPI_MODE 3

bool lcd_init = false;
int lcd_delay = 0;

void keyboard_post_init_kb(void) {

    lcd240 = qp_load_image_mem(gfx_lcd240);
    gml240 = qp_load_image_mem(gfx_gml240);
    lower240 = qp_load_image_mem(gfx_lower240);

    // Turn on the LCD BL
    setPinOutput(LCD_BL_PIN);
    writePinHigh(LCD_BL_PIN);
    // writePinLow(LCD_BL_PIN);

    // Let the LCD get some power...
    wait_ms(150);

    // Initialise the LCD
    lcd = qp_st7789_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
    qp_init(lcd, QP_ROTATION_0);

    // Turn on the LCD and clear the display
    // kb_state.lcd_power = 1;
    qp_power(lcd, true);

    // if (lcd240 != NULL) {
    //   qp_rect(lcd, 0, 0, 239, 239, HSV_GOLDENROD, true);
    // } else {
    //   qp_rect(lcd, 0, 0, 239, 239, HSV_RED, true);
    // }

    // qp_setpixel(lcd, 10, 10, HSV_WHITE);

    // qp_drawimage(lcd, 0, 0, lcd240);
    // qp_drawimage(lcd, 0, 0, gml240);
    // qp_drawimage_recolor(lcd, 0, 0, gml240, HSV_GML_GOLD, HSV_BLACK);
    qp_drawimage_recolor(lcd, 0, 0, lower240, HSV_GML_GOLD, HSV_BLACK);

    qp_flush(lcd);

#ifdef CONSOLE_ENABLE
    print("LCD initialised\n");
#endif

    // Allow for user post-init
    keyboard_post_init_user();
}



//----------------------------------------------------------
// Housekeeping

void housekeeping_task_kb(void) {
    // qp_rect(lcd, 0, 0, 239, 239, HSV_AZURE, true);

    // qp_setpixel(lcd, lcd_delay/256 + lcd_delay, lcd_delay, HSV_WHITE);

    // qp_flush(lcd);

    lcd_delay ++;

    // qp_drawimage_recolor(lcd, 0, 0, gml240, lcd_delay % 256, 198, 255, HSV_BLACK);


//     if (!lcd_init && lcd_delay > 4000) {

//         // Turn on the LCD BL
//         setPinOutput(LCD_BL_PIN);
//         writePinHigh(LCD_BL_PIN);
//         // writePinLow(LCD_BL_PIN);

//         // Let the LCD get some power...
//         wait_ms(150);

//         // Initialise the LCD
//         lcd = qp_st7789_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
//         qp_init(lcd, QP_ROTATION_0);

//         // Turn on the LCD and clear the display
//         // kb_state.lcd_power = 1;
//         qp_power(lcd, true);
//         qp_rect(lcd, 0, 0, 239, 239, HSV_AZURE, true);

//         qp_setpixel(lcd, 10, 10, HSV_WHITE);

//         qp_flush(lcd);

//         // // Turn on the LCD backlight
//         // backlight_enable();
//         // backlight_level(BACKLIGHT_LEVELS);

//     // #ifdef CONSOLE_ENABLE
//         print("LCD initialised\n");
//     // #endif

//         lcd_init = true;

//     }
}


//     bool            hue_redraw = false;
//     static uint16_t last_hue   = 0xFFFF;
// #if defined(RGB_MATRIX_ENABLE)
//     uint16_t curr_hue = rgb_matrix_get_hue();
// #else  // defined(RGB_MATRIX_ENABLE)
//     uint16_t curr_hue = 0;
// #endif // defined(RGB_MATRIX_ENABLE)
//     if (last_hue != curr_hue) {
//         last_hue   = curr_hue;
//         hue_redraw = true;
//     }

//     bool            layer_state_redraw = false;
//     static uint32_t last_layer_state   = 0;
//     if (last_layer_state != layer_state) {
//         last_layer_state   = layer_state;
//         layer_state_redraw = true;
//     }

//     bool                     power_state_redraw = false;
//     static usbpd_allowance_t last_current_state = (usbpd_allowance_t)(~0);
//     if (last_current_state != kb_state.current_setting) {
//         last_current_state = kb_state.current_setting;
//         power_state_redraw = true;
//     }

//     bool            scan_redraw      = false;
//     static uint32_t last_scan_update = 0;
//     if (timer_elapsed32(last_scan_update) > 125) {
//         last_scan_update = timer_read32();
//         scan_redraw      = true;
//     }

//     bool            wpm_redraw      = false;
//     static uint32_t last_wpm_update = 0;
//     if (timer_elapsed32(last_wpm_update) > 125) {
//         last_wpm_update = timer_read32();
//         wpm_redraw      = true;
//     }

// #if defined(RGB_MATRIX_ENABLE)
//     bool            rgb_effect_redraw = false;
//     static uint16_t last_effect       = 0xFFFF;
//     uint8_t         curr_effect       = rgb_matrix_config.mode;
//     if (last_effect != curr_effect) {
//         last_effect       = curr_effect;
//         rgb_effect_redraw = true;
//     }
// #endif // defined(RGB_MATRIX_ENABLE)

//     // Show the Djinn logo and two vertical bars on both sides
//     if (hue_redraw) {
//         qp_drawimage_recolor(lcd, 120 - djinn_logo->width / 2, 32, djinn_logo, curr_hue, 255, 255, curr_hue, 255, 0);
//         qp_rect(lcd, 0, 0, 8, 319, curr_hue, 255, 255, true);
//         qp_rect(lcd, 231, 0, 239, 319, curr_hue, 255, 255, true);
//     }

//     int ypos = 4;

//     // Show layer info on the left side
//     if (is_keyboard_left()) {
//         char buf[64] = {0};
//         int  xpos    = 16;

// #if defined(RGB_MATRIX_ENABLE)
//         if (hue_redraw || rgb_effect_redraw) {
//             static int max_rgb_xpos = 0;
//             xpos                    = 16;
//             snprintf(buf, sizeof(buf), "rgb: %s", rgb_matrix_name(curr_effect));

//             for (int i = 5; i < sizeof(buf); ++i) {
//                 if (buf[i] == 0)
//                     break;
//                 else if (buf[i] == '_')
//                     buf[i] = ' ';
//                 else if (buf[i - 1] == ' ')
//                     buf[i] = toupper(buf[i]);
//                 else if (buf[i - 1] != ' ')
//                     buf[i] = tolower(buf[i]);
//             }

//             xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
//             if (max_rgb_xpos < xpos) {
//                 max_rgb_xpos = xpos;
//             }
//             qp_rect(lcd, xpos, ypos, max_rgb_xpos, ypos + thintel->line_height, 0, 0, 0, true);
//         }

//         ypos += thintel->line_height + 4;
// #endif // defined(RGB_MATRIX_ENABLE)

//         if (hue_redraw || layer_state_redraw) {
//             extern const char *current_layer_name(void);
//             const char        *layer_name = current_layer_name();

//             static int max_layer_xpos = 0;
//             xpos                      = 16;
//             snprintf(buf, sizeof(buf), "layer: %s", layer_name);
//             xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
//             if (max_layer_xpos < xpos) {
//                 max_layer_xpos = xpos;
//             }
//             qp_rect(lcd, xpos, ypos, max_layer_xpos, ypos + thintel->line_height, 0, 0, 0, true);
//         }

//         ypos += thintel->line_height + 4;

//         if (hue_redraw || power_state_redraw) {
//             static int max_power_xpos = 0;
//             xpos                      = 16;
//             snprintf(buf, sizeof(buf), "power: %s", usbpd_str(kb_state.current_setting));
//             xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
//             if (max_power_xpos < xpos) {
//                 max_power_xpos = xpos;
//             }
//             qp_rect(lcd, xpos, ypos, max_power_xpos, ypos + thintel->line_height, 0, 0, 0, true);
//         }

//         ypos += thintel->line_height + 4;

//         if (hue_redraw || scan_redraw) {
//             static int max_scans_xpos = 0;
//             xpos                      = 16;
//             snprintf(buf, sizeof(buf), "scans: %d", (int)theme_state.scan_rate);
//             xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
//             if (max_scans_xpos < xpos) {
//                 max_scans_xpos = xpos;
//             }
//             qp_rect(lcd, xpos, ypos, max_scans_xpos, ypos + thintel->line_height, 0, 0, 0, true);
//         }

//         ypos += thintel->line_height + 4;

//         if (hue_redraw || wpm_redraw) {
//             static int max_wpm_xpos = 0;
//             xpos                    = 16;
//             snprintf(buf, sizeof(buf), "wpm: %d", (int)get_current_wpm());
//             xpos += qp_drawtext_recolor(lcd, xpos, ypos, thintel, buf, curr_hue, 255, 255, curr_hue, 255, 0);
//             if (max_wpm_xpos < xpos) {
//                 max_wpm_xpos = xpos;
//             }
//             qp_rect(lcd, xpos, ypos, max_wpm_xpos, ypos + thintel->line_height, 0, 0, 0, true);
//         }

//         ypos += thintel->line_height + 4;
//     }

//     // Show LED lock indicators on the right side
//     if (!is_keyboard_left()) {
//         static led_t last_led_state = {0};
//         if (hue_redraw || last_led_state.raw != host_keyboard_led_state().raw) {
//             last_led_state.raw = host_keyboard_led_state().raw;
//             qp_drawimage_recolor(lcd, 239 - 12 - (32 * 3), 0, last_led_state.caps_lock ? lock_caps_on : lock_caps_off, curr_hue, 255, last_led_state.caps_lock ? 255 : 32, curr_hue, 255, 0);
//             qp_drawimage_recolor(lcd, 239 - 12 - (32 * 2), 0, last_led_state.num_lock ? lock_num_on : lock_num_off, curr_hue, 255, last_led_state.num_lock ? 255 : 32, curr_hue, 255, 0);
//             qp_drawimage_recolor(lcd, 239 - 12 - (32 * 1), 0, last_led_state.scroll_lock ? lock_scrl_on : lock_scrl_off, curr_hue, 255, last_led_state.scroll_lock ? 255 : 32, curr_hue, 255, 0);
//         }
//     }
