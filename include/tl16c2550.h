/**
 * @file tl16c2550.h
 * @brief TL16C2550 UART Serial Driver for Commander X16
 * 
 * This header provides the interface for the TL16C2550 dual UART
 * serial communication driver for the Commander X16.
 */

#ifndef TL16C2550_H
#define TL16C2550_H

#include <stdint.h>

/* UART Base Addresses for Commander X16 */
#define UART_BASE_A   0x9F60
#define UART_BASE_B   0x9F68

/* Register Offsets */
#define UART_RBR      0  /* Receiver Buffer Register (read) */
#define UART_THR      0  /* Transmitter Holding Register (write) */
#define UART_IER      1  /* Interrupt Enable Register */
#define UART_IIR      2  /* Interrupt Identification Register (read) */
#define UART_FCR      2  /* FIFO Control Register (write) */
#define UART_LCR      3  /* Line Control Register */
#define UART_MCR      4  /* Modem Control Register */
#define UART_LSR      5  /* Line Status Register */
#define UART_MSR      6  /* Modem Status Register */
#define UART_SCR      7  /* Scratch Register */

/* Line Status Register Bits */
#define LSR_DATA_READY    0x01
#define LSR_OVERRUN_ERR   0x02
#define LSR_PARITY_ERR    0x04
#define LSR_FRAMING_ERR   0x08
#define LSR_BREAK_INT     0x10
#define LSR_THR_EMPTY     0x20
#define LSR_TX_EMPTY      0x40
#define LSR_FIFO_ERR      0x80

/**
 * Initialize the specified UART
 * @param uart_base Base address of UART (UART_BASE_A or UART_BASE_B)
 * @param baud_rate Desired baud rate
 */
void uart_init(uint16_t uart_base, uint32_t baud_rate);

/**
 * Send a character via UART
 * @param uart_base Base address of UART
 * @param c Character to send
 */
void uart_putc(uint16_t uart_base, char c);

/**
 * Receive a character from UART
 * @param uart_base Base address of UART
 * @return Received character
 */
char uart_getc(uint16_t uart_base);

/**
 * Check if data is available to read
 * @param uart_base Base address of UART
 * @return Non-zero if data available
 */
uint8_t uart_data_ready(uint16_t uart_base);

/**
 * Check if transmitter is ready
 * @param uart_base Base address of UART
 * @return Non-zero if ready to transmit
 */
uint8_t uart_tx_ready(uint16_t uart_base);

#endif /* TL16C2550_H */
