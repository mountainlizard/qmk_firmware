#include_next <board.h>

#ifdef STM32_LSECLK
#undef STM32_LSECLK
#endif // STM32_LSECLK
#define STM32_LSECLK 32768U

#ifdef STM32_HSECLK
#undef STM32_HSECLK
#endif // STM32_HSECLK
#define STM32_HSECLK 12000000U

#ifdef STM32_VDD
#undef STM32_VDD
#endif // STM32_VDD
#define STM32_VDD 330U

#ifdef STM32F407xx
#undef STM32F407xx
#endif // STM32F407xx
#define STM32F405xx
