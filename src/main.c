#include "RP2350.h"
#include "hardware/regs/resets.h"
#include "hardware/platform_defs.h"

#include <stdint.h>

void delay(int count) {
    for (volatile int i = 0; i < count; i++){
        __asm __volatile__("nop");
    }
}


int main(){
    delay(1000);


    // Reset and configure the onboard LED (GPIO25)
    IO_BANK0->GPIO25_CTRL = 0x05; // Set GPIO25 to SIO function (for onboard LED)
    PADS_BANK0->GPIO25 = 0x0;
    delay(1000);
    SIO->GPIO_OE_SET = (1 << 25); // Set GPIO25 as output
    delay(1000);
    SIO->GPIO_OUT_SET = (1 << 25); // Turn on LED

    while (1)
    {
        SIO->GPIO_OUT_XOR = (1 << 25); // Toggle LED state
        delay(1000000); // Simple delay
    }
    

    return 0;
}

