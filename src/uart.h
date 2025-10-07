#ifndef _UART_H_
#define _UART_H_
#include <stdint.h>
#include "RP2350.h"

/**
 * Initialize UART with specified baud rate
 * 
 * @param uart_num: uart0 or uart1
 * @param tx_pin: GPIO pin for TX
 * @param rx_pin: GPIO pin for RX
 * @param baudrate: Desired baud rate (e.g., 115200)
 * 
 * Default config: 8 data bits, no parity, 1 stop bit (8N1)
 */
void* uart_init(int uart_num, uint32_t tx_pin, uint32_t rx_pin, uint32_t baudrate);

/**
 * Get UART hardware instance by number
 * 
 * @param uart_num: 0 for uart0, 1 for uart1
 * @return Pointer to uart_hw_t structure
 */
void* get_uart(int uart_num);

/**
 * Transmit a single character
 */
void uart_putc(void *uart, char c);

/**
 * Transmit a string
 */
void uart_puts(void *uart, const char *str);

/**
 * Receive a single character (blocking)
 */
char uart_getc(int uart);

const char* uart_gets(void *uart, char *buf, int maxlen);

/**
 * Check if data is available to read
 */
int uart_is_readable(void *uart);

/**
 * Check if UART is ready to transmit
 */
int uart_is_writable(void *uart);

/**
 * Wait for all pending transmissions to complete
 */
void uart_tx_wait_blocking(void *uart);

#endif // _UART_H_