#ifndef LED_H
#define LED_H

#include <stdint.h>

void led_init(uint32_t gpio_pin);

void led_on(uint32_t gpio_pin);

void led_off(uint32_t gpio_pin);

void led_toggle(uint32_t gpio_pin);


#endif // LED_H