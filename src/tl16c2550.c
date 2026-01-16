/**
 * @file tl16c2550.c
 * @brief TL16C2550 UART Driver Implementation for Commander X16
 * 
 * NOTE: This is a TEMPLATE/FRAMEWORK implementation.
 * The actual hardware initialization and timing details need to be
 * implemented based on your specific hardware configuration.
 */

#include <stddef.h>  /* For NULL definition */
#include "tl16c2550.h"

/* UART register base address - adjust for your hardware */
#define UART_BASE 0x9F60

/* Register offsets */
#define UART_RBR  (UART_BASE + 0)  /* Receiver Buffer Register */
#define UART_THR  (UART_BASE + 0)  /* Transmitter Holding Register */
#define UART_IER  (UART_BASE + 1)  /* Interrupt Enable Register */
#define UART_FCR  (UART_BASE + 2)  /* FIFO Control Register */
#define UART_LCR  (UART_BASE + 3)  /* Line Control Register */
#define UART_MCR  (UART_BASE + 4)  /* Modem Control Register */
#define UART_LSR  (UART_BASE + 5)  /* Line Status Register */
#define UART_MSR  (UART_BASE + 6)  /* Modem Status Register */

/* LSR bits */
#define LSR_DR    0x01  /* Data Ready */
#define LSR_THRE  0x20  /* Transmitter Holding Register Empty */

unsigned char uart_init(void)
{
    /* 
     * TODO: Implement proper UART initialization sequence
     * 
     * A complete implementation should:
     * 1. Set the baud rate divisor (using DLL/DLM registers)
     * 2. Configure line control (data bits, stop bits, parity)
     * 3. Enable/configure FIFOs
     * 4. Set modem control signals if needed
     * 5. Enable interrupts if required
     * 
     * This is a placeholder - adapt to your hardware requirements.
     */
    return 0;
}

unsigned char uart_putc(unsigned char data)
{
    /* 
     * NOTE: This will block indefinitely if UART is not initialized
     * or hardware is not present. Production code should add timeout.
     */
    
    /* Wait for transmitter to be ready */
    while (!(*(volatile unsigned char*)UART_LSR & LSR_THRE))
        ;
    
    /* Send the byte */
    *(volatile unsigned char*)UART_THR = data;
    
    return 0;
}

unsigned char uart_getc(unsigned char *data)
{
    if (data == NULL) {
        return 1; /* Error: NULL pointer */
    }
    
    /* 
     * NOTE: This will block indefinitely if UART is not initialized
     * or hardware is not present. Production code should add timeout.
     */
    
    /* Wait for data to be available */
    while (!(*(volatile unsigned char*)UART_LSR & LSR_DR))
        ;
    
    /* Read the byte */
    *data = *(volatile unsigned char*)UART_RBR;
    
    return 0;
}

unsigned char uart_data_available(void)
{
    return (*(volatile unsigned char*)UART_LSR & LSR_DR) ? 1 : 0;
}
