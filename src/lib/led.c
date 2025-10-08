#include "led.h"
#include "RP2350.h"

const uint32_t MAX_NUM_PINS = 30;

void SetNthElement(uint32_t* base_ptr, uint32_t offset, uint32_t value) {
    // dangerous stuff, but only way for to provide generic access
    base_ptr[offset] = value;
}

#define FUNC_SEL_GPIO 0x05


void led_init(uint32_t gpio_pin) {
    if (gpio_pin >= MAX_NUM_PINS) {
        return;
    }
    SetNthElement((uint32_t*)IO_BANK0, (2 * gpio_pin) + 1, FUNC_SEL_GPIO);

    SetNthElement((uint32_t*)&(PADS_BANK0->GPIO0), gpio_pin, 0x0);
    SIO->GPIO_OE_SET = (1 << gpio_pin);
}

void led_on(uint32_t gpio_pin) {
    if (gpio_pin >= MAX_NUM_PINS) {
        return;
    }
    SIO->GPIO_OUT_SET = (1 << gpio_pin);
}

void led_off(uint32_t gpio_pin) {
    if (gpio_pin >= MAX_NUM_PINS) {
        return;
    }
    SIO->GPIO_OUT_CLR = (1 << gpio_pin);
}

void led_toggle(uint32_t gpio_pin) {
    if (gpio_pin >= MAX_NUM_PINS) {
        return;
    }
    SIO->GPIO_OUT_XOR = (1 << gpio_pin);
}