#include <stdint.h>

#include "RP2350.h"
#include "hardware/platform_defs.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/regs/resets.h"

#include "led.h"

#define ONBOARD_LED_GPIO 25

void delay(int count) {
  for (volatile int i = 0; i < count; i++) {
    __asm __volatile__("nop");
  }
}

int main() {
  delay(1000);

  led_init(ONBOARD_LED_GPIO);
  led_on(ONBOARD_LED_GPIO);

  while (1) {
    led_toggle(ONBOARD_LED_GPIO);
    delay(1000000);
  }

  return 0;
}
