#pragma once

#include "quantum.h"
#include "qp.h"

extern painter_device_t lcd;

#define LAYOUT( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b  \
) { \
  { k01, k05, k04, k03, k00, k02 },  \
  { k11, k15, k14, k13, k10, k12 },  \
  { k21, k25, k24, k23, k20, k22 },  \
  { k31, k35, k34, k33, k30, k32 },  \
  { k06, k07, k0a, k0b, k09, k08 },  \
  { k16, k17, k1a, k1b, k19, k18 },  \
  { k26, k27, k2a, k2b, k29, k28 },  \
  { k36, k37, k3a, k3b, k39, k38 }   \
}
