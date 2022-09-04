# Displays

Will drive two Adafruit featherwings, both using I2C only:

1. 14-segment Alphanumeric
2. 16x8 LED Matrix

Both are expected to be at their default addresses.

I2C is connected as specified in `gml_01/config.h`:

```c
#define I2C1_SDA_PIN GP16
#define I2C1_SCL_PIN GP17
```
