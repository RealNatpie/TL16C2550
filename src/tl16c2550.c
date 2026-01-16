/**
 * @file tl16c2550.c
 * @brief TL16C2550 UART Serial Driver Implementation
 */

#include "tl16c2550.h"

/* Helper function to write to UART register */
static void uart_write_reg(uint16_t uart_base, uint8_t reg, uint8_t value) {
    *((volatile uint8_t*)(uart_base + reg)) = value;
}

/* Helper function to read from UART register */
static uint8_t uart_read_reg(uint16_t uart_base, uint8_t reg) {
    return *((volatile uint8_t*)(uart_base + reg));
}

void uart_init(uint16_t uart_base, uint32_t baud_rate) {
    uint16_t divisor;
    
    /* Calculate divisor for baud rate (assuming 1.8432 MHz clock) */
    divisor = (uint16_t)(1843200UL / (16UL * baud_rate));
    
    /* Set DLAB to access divisor */
    uart_write_reg(uart_base, UART_LCR, 0x80);
    
    /* Set divisor */
    uart_write_reg(uart_base, 0, (uint8_t)(divisor & 0xFF));        /* DLL */
    uart_write_reg(uart_base, 1, (uint8_t)((divisor >> 8) & 0xFF)); /* DLM */
    
    /* Clear DLAB, set 8N1 (8 data bits, no parity, 1 stop bit) */
    uart_write_reg(uart_base, UART_LCR, 0x03);
    
    /* Enable and clear FIFOs */
    uart_write_reg(uart_base, UART_FCR, 0x07);
    
    /* Disable interrupts */
    uart_write_reg(uart_base, UART_IER, 0x00);
    
    /* Set RTS/DTR */
    uart_write_reg(uart_base, UART_MCR, 0x03);
}

void uart_putc(uint16_t uart_base, char c) {
    /* Wait until transmitter is ready */
    while (!uart_tx_ready(uart_base)) {
        /* Wait */
    }
    
    /* Send character */
    uart_write_reg(uart_base, UART_THR, (uint8_t)c);
}

char uart_getc(uint16_t uart_base) {
    /* Wait until data is available */
    while (!uart_data_ready(uart_base)) {
        /* Wait */
    }
    
    /* Read character */
    return (char)uart_read_reg(uart_base, UART_RBR);
}

uint8_t uart_data_ready(uint16_t uart_base) {
    return uart_read_reg(uart_base, UART_LSR) & LSR_DATA_READY;
}

uint8_t uart_tx_ready(uint16_t uart_base) {
    return uart_read_reg(uart_base, UART_LSR) & LSR_THR_EMPTY;
}
