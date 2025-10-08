#include "led.h"
#include "RP2350.h"
#include <stddef.h>

const uint32_t MAX_NUM_PINS = 30;

void SetNthElement(uint32_t* base_ptr, uint32_t offset, uint32_t value) {
    // Ensure we have a valid pointer
    if (base_ptr == NULL) {
        return;
    }

    volatile uint32_t* reg_ptr = (volatile uint32_t*)base_ptr;
    reg_ptr[offset] = value;
}

uint32_t GetControlRegIndexInIoBank(uint32_t gpio_pin) {
    if (gpio_pin >= MAX_NUM_PINS) {
        return 0xFFFFFFFF; // Invalid pin
    }
    // struct is laid out with status and control registers interleaved
    volatile uint32_t* reg_ptr = (volatile uint32_t*)IO_BANK0;
    return (2 * gpio_pin) + 1;
}

#define FUNC_SEL_GPIO 0x05


void led_init(uint32_t gpio_pin) {
    if (gpio_pin >= MAX_NUM_PINS) {
        return;
    }
    SetNthElement((uint32_t*)IO_BANK0, GetControlRegIndexInIoBank(gpio_pin), FUNC_SEL_GPIO);

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