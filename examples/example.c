/**
 * @file example.c
 * @brief Example usage of the TL16C2550 serial library
 * 
 * This example demonstrates how to use the library in your Commander X16 project.
 * To compile this example:
 *   make
 *   cl65 -t cx16 -I build -o example.prg examples/example.c -L build -ltl16c2550
 */

#include <stdio.h>
#include "tl16c2550.h"

int main(void) {
    char c;
    
    /* Initialize UART A at 9600 baud */
    uart_init(UART_BASE_A, 9600);
    
    /* Send a welcome message */
    printf("TL16C2550 Serial Example\n");
    printf("Type characters to echo them back\n");
    
    /* Simple echo loop */
    while (1) {
        /* Check if data is available */
        if (uart_data_ready(UART_BASE_A)) {
            /* Read character */
            c = uart_getc(UART_BASE_A);
            
            /* Echo it back */
            uart_putc(UART_BASE_A, c);
            
            /* Exit on ESC */
            if (c == 27) {
                break;
            }
        }
    }
    
    printf("\nExiting...\n");
    return 0;
}
