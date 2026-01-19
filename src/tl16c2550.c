/**
 * @file tl16c2550.c
 * @brief TL16C2550 UART Serial Driver Implementation
 */

#include "tl16c2550.h"
#include <stdlib.h>
#include <cx16.h>


/* Calculate divisor for baud rate */
unsigned int findDivisor(unsigned long crystal_clock, unsigned long baud_rate) {
    return (unsigned int)(crystal_clock / baud_rate);
}

/**
 * Create and initialize a UART instance (internal - actual creation logic)
 */
UART_Instance* createUARTWithDivisor(unsigned long crystal_speed, unsigned long baudrate, unsigned int divisor, unsigned int base_address, unsigned char databits, Parity parity, unsigned char stop_bits) {
    UART_Instance* uart;
    BaudRate baud_enum;
    unsigned char lcr;
    unsigned char i;
    static const unsigned long baud_rates[] = {
        50, 300, 600, 1200, 2400, 4800, 9600, 19200,
        38400, 57600, 115200, 230400, 460800, 921600
    };
    
    /* Validate parameters */
    if (databits < 5 || databits > 8) {
        return NULL;  /* Invalid data bits */
    }
    
    if (stop_bits != 1 && stop_bits != 2) {
        return NULL;  /* Invalid stop bits */
    }
    
    if (parity > PARITY_EVEN) {
        return NULL;  /* Invalid parity */
    }
    
    /* Allocate memory for UART instance */
    uart = (UART_Instance*)malloc(sizeof(UART_Instance));
    if (uart == NULL) {
        return NULL;  /* malloc failed */
    }
    
    /* Allocate input buffer */
    uart->input_buffer = (unsigned char*)malloc(UART_BUFFER_SIZE);
    if (uart->input_buffer == NULL) {
        free(uart);
        return NULL;
    }
    
    /* Allocate output buffer */
    uart->output_buffer = (unsigned char*)malloc(UART_BUFFER_SIZE);
    if (uart->output_buffer == NULL) {
        free(uart->input_buffer);
        free(uart);
        return NULL;
    }
    
    /* Initialize buffer pointers */
    uart->input_head = 0;
    uart->input_tail = 0;
    uart->output_head = 0;
    uart->output_tail = 0;
    
    /* Set base address */
    uart->base_address = base_address;
    
    /* Set crystal speed (already divided by 16) */
    uart->crystal_speed = crystal_speed;
    
    /* Map numeric baud rate to enum and set baudrate */
    baud_enum = BR_CUSTOM;
    for (i = 0; i < 14; i++) {
        if (baud_rates[i] == baudrate) {
            baud_enum = (BaudRate)i;
            break;
        }
    }
    
    uart->baudrate = baud_enum;
    
    /* If custom baud rate, store the value */
    if (baud_enum == BR_CUSTOM) {
        uart->custom_baudrate = baudrate;
    }
    else{
        uart->custom_baudrate = 0;
    }
    
    /* Set divisor */
    uart->divisor = divisor;
    
    /* Build LCR register value */
    /* Set data bits (bits 0-1): 5=0x00, 6=0x01, 7=0x02, 8=0x03 */
    lcr = databits - 5;
    
    /* Set stop bits (bit 2) */
    if (stop_bits == 2) {
        lcr |= 0x04;  /* Set bit 2 for 2 stop bits */
    }
    
    /* Set parity (bits 3-5) */
    if (parity == PARITY_ODD) {
        lcr |= 0x08;  /* Enable parity (bit 3) */
        /* Odd parity: bit 4 = 0 */
    } else if (parity == PARITY_EVEN) {
        lcr |= 0x18;  /* Enable parity (bit 3) and set even parity (bit 4) */
    }
    /* PARITY_NONE: no additional bits set */
    
    uart->lcr = lcr;
    for(i=0;i<UART_BUFFER_SIZE;i++){
        uart->input_buffer[i]=0;
        uart->output_buffer[i]=0;
    }
    uart->in_buffer_status = BUF_EMPTY;
    uart->out_buffer_status = BUF_EMPTY;
    return uart;
}

/**
 * Create and initialize a UART instance (calculates divisor from baud rate)
 */
UART_Instance* createUART(unsigned long crystal_speed, unsigned long baudrate, unsigned int base_address, unsigned char databits, Parity parity, unsigned char stop_bits) {
    unsigned int divisor = findDivisor(crystal_speed, baudrate);
    return createUARTWithDivisor(crystal_speed, baudrate, divisor, base_address, databits, parity, stop_bits);
}
