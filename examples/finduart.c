/**cl65 -t cx16 example.c libtl16c2550.lib -o example.prg -L /path/to/cc65/lib -lc
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
#include <cx16.h>

int main(void) {
    unsigned int uart_addresses[MAX_UARTS];
    unsigned char found_count;
    unsigned char i;
    
    printf("Scanning for UART devices...\n");
    
    found_count = scanUARTs(uart_addresses);
    
    printf("Found %u UART(s)\n", found_count);
    
    if (found_count > 0) {
        printf("\nUART Addresses:\n");
        for (i = 0; i < found_count; i++) {
            printf("  UART %u: $%04X\n", i, uart_addresses[i]);
        }
    } else {
        printf("No UARTs detected.\n");
    }
    
    return 0;
}
