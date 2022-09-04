
# TODO remove, specified in info.json?
# MCU = RP2040
# BOOTLOADER = rp2040

# TODO remove, specified in keymap rules.mk?
# OLED_ENABLE = yes
# OLED_DRIVER = SSD1306

# PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.


OPT_DEFS += -DHAL_USE_I2C=TRUE

# TODO remove, specified in info.json?
# CONSOLE_ENABLE = yes

# For trackball
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = adns9800

BOARD = GENERIC_RP_RP2040
