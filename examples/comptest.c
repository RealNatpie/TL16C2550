#include <stdio.h>
#include <stdlib.h>
#include <cx16.h>
unsigned int uart_addresses[20];

int main(void) {
    unsigned char found_count = 0;
    unsigned char i;
    

    for(i=0; i<20; i++) {
        uart_addresses[i] = 7*i;
        found_count++;
    }   
    printf("Hello, World!\n");
    for(i=0; i<found_count; i++) {
        printf("UART %u Address: $%04X\n", i, uart_addresses[i]);
    }   
    return 0;
}
