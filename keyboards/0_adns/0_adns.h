#pragma once

#include "quantum.h"

#define SPI_SCK_PIN B13
#define SPI_MISO_PIN B14
#define SPI_MOSI_PIN B15

#define LAYOUT( \
  K00,  \
  K01  \
) { \
  { K00 }, \
  { K01 } \
}
