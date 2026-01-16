/**
 * @file example.c
 * @brief Example usage of the TL16C2550 UART library
 * 
 * This example demonstrates basic UART operations using the library.
 * To build this example with the library:
 *   cc65 -t cx16 -I include -o example.s example.c
 *   ca65 -t cx16 -o example.o example.s
 *   ld65 -t cx16 -o example.prg example.o lib/tl16c2550.lib
 */

#include "tl16c2550.h"

int main(void)
{
    unsigned char rx_data;
    
    /* Initialize the UART */
    if (uart_init() != 0) {
        /* Initialization failed */
        return 1;
    }
    
    /* Send "Hello, UART!" */
    uart_putc('H');
    uart_putc('e');
    uart_putc('l');
    uart_putc('l');
    uart_putc('o');
    uart_putc(',');
    uart_putc(' ');
    uart_putc('U');
    uart_putc('A');
    uart_putc('R');
    uart_putc('T');
    uart_putc('!');
    uart_putc('\r');
    uart_putc('\n');
    
    /* Echo back any received data */
    while (1) {
        if (uart_data_available()) {
            if (uart_getc(&rx_data) == 0) {
                uart_putc(rx_data);  /* Echo the character */
            }
        }
    }
    
    return 0;
}
