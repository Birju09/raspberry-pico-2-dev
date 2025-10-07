#include <stdint.h>

#include "RP2350.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/regs/resets.h"

#define ONBOARD_LED_GPIO 25

void delay(int count) {
  for (volatile int i = 0; i < count; i++) {
    __asm __volatile__("nop");
  }
}

int main() {
  delay(1000);

  IO_BANK0->GPIO25_CTRL = IO_BANK0_GPIO25_CTRL_FUNCSEL_VALUE_SIOB_PROC_25;
  PADS_BANK0->GPIO25 = 0x0;
  delay(1000);
  SIO->GPIO_OE_SET = (1 << ONBOARD_LED_GPIO);
  delay(1000);
  SIO->GPIO_OUT_SET = (1 << ONBOARD_LED_GPIO);

  while (1) {
    SIO->GPIO_OUT_XOR = (1 << ONBOARD_LED_GPIO);
    delay(1000000);
  }

  return 0;
}
