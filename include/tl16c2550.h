/**
 * @file tl16c2550.h
 * @brief TL16C2550 UART Driver for Commander X16
 * 
 * This library provides serial communication drivers for Commander X16
 * devices using the TL16C2550 and compatible UARTs.
 */

#ifndef TL16C2550_H
#define TL16C2550_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the UART
 * @return 0 on success, non-zero on error
 */
unsigned char uart_init(void);

/**
 * @brief Send a byte through the UART
 * @param data The byte to send
 * @return 0 on success, non-zero on error
 */
unsigned char uart_putc(unsigned char data);

/**
 * @brief Receive a byte from the UART
 * @param data Pointer to store the received byte
 * @return 0 on success, non-zero on error
 */
unsigned char uart_getc(unsigned char *data);

/**
 * @brief Check if data is available to read
 * @return Non-zero if data is available, 0 otherwise
 */
unsigned char uart_data_available(void);

#ifdef __cplusplus
}
#endif

#endif /* TL16C2550_H */
