#include <stdint.h>
#include "uart.h"
#include "RP2350.h"

static inline void busy_wait_us(uint32_t us) {
    // Rough delay - assumes ~125MHz clock
    // 125 cycles per microsecond
    for (volatile uint32_t i = 0; i < us * 125; i++) {
        __asm volatile ("nop");
    }
}

void uart_init(int uart_num, uint32_t tx_pin, uint32_t rx_pin, uint32_t baudrate) {
}

void* get_uart(int uart_num) {
}

void uart_putc(void *uart, char c) {
    // Wait until TX FIFO is not full
    while (uart->FR & UART_FR_TXFF);
    
    // Write character to data register
    uart->DR = c;
}

void uart_puts(uart_hw_t *uart, const char *str) {
    while (*str) {
        // Handle line endings
        if (*str == '\n') {
            uart_putc(uart, '\r');
        }
        uart_putc(uart, *str++);
    }
}

char uart_getc(uart_hw_t *uart) {
    // Wait until RX FIFO is not empty
    while (uart->FR & UART_FR_RXFE);
    
    // Read character from data register
    return (char)(uart->DR & 0xFF);
}

/**
 * Check if data is available to read
 */
int uart_is_readable(uart_hw_t *uart) {
    return !(uart->FR & UART_FR_RXFE);
}

int uart_is_writable(uart_hw_t *uart) {
    return !(uart->FR & UART_FR_TXFF);
}

void uart_tx_wait_blocking(uart_hw_t *uart) {
    while (uart->FR & UART_FR_BUSY);
}