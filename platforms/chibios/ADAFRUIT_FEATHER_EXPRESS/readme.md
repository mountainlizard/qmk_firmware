The files in this folder are generated using fmpp from the contents of the `cfg` directory.
First, install [fmpp](https://sourceforge.net/projects/fmpp/) - you really do need to actually unzip it and run it from the zip, there is no package for debian/ubuntu.
So say you unzip it to `~/fmpp`, go to `qmk_firmware/platforms/chibios/ADAFRUIT_FEATHER_EXPRESS/cfg` and then run `~/fmpp/bin/fmpp -C board.fmpp`, this will generate the `borad.c`, `board.h` and `board.mk` files.

Then update `board/board.mk` to match qmk layout (it should be possible to address this by using a different template, but this is easier):

```
# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/board/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/board

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
```

Next we might need to add mcu to mcu_selection.mk, and the name to keyboard.jsonschema