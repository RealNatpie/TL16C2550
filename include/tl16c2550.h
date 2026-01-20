/**
 * @file tl16c2550.h
 * @brief TL16C2550 UART Serial Driver for Commander X16
 * 
 * This header provides the interface for the TL16C2550 dual UART
 * serial communication driver for the Commander X16.
 */

#ifndef TL16C2550_H
#define TL16C2550_H



/* NULL definition */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* Baud rate enum */
typedef enum {
    BR_50,
    BR_300,
    BR_600,
    BR_1200,
    BR_2400,
    BR_4800,
    BR_9600,
    BR_19200,
    BR_38400,
    BR_57600,
    BR_115200,
    BR_230400,
    BR_460800,
    BR_921600,
    BR_CUSTOM
} BaudRate;

/* Parity enum */
typedef enum {
    PARITY_NONE,
    PARITY_ODD,
    PARITY_EVEN
} Parity;

/* UART Instance structure for managing multiple UART ports */
typedef struct {
    unsigned int base_address;          /* Base address of the UART */
    unsigned char *input_buffer;        /* Pointer to input (receive) buffer */
    unsigned char in_buffer_status;     /* Status of the buffer (e.g., full, empty) */
    unsigned char *output_buffer;       /* Pointer to output (transmit) buffer */
    unsigned char out_buffer_status;    /* Status of the buffer (e.g., full, empty) */
    unsigned char input_head;           /* Head offset for input buffer */
    unsigned char input_tail;           /* Tail offset for input buffer */
    unsigned char output_head;          /* Head offset for output buffer */
    unsigned char output_tail;          /* Tail offset for output buffer */
    unsigned long crystal_speed;        /* Crystal clock speed divided by 16 */
    unsigned int divisor;               /* Baud rate divisor value */
    BaudRate baudrate;                  /* Current baud rate setting */
    unsigned custom_baudrate;           /* Custom baud rate value */
    unsigned char lcr;                  /* Line Control Register (word length, stop bits, parity) */
} UART_Instance;



/* UART Base Addresses for Commander X16 */
/* $9F60 through $9FF8 are posible locations seperate by 8 bytes */
#define UART_BASE   0x9F60
#define UART_OFFSETS 0x08

/* Maximum number of UART instances */
#define MAX_UARTS   20

/* UART buffer size (256 bytes for 8-bit circular buffer) */
#define UART_BUFFER_SIZE 256

/* Clock constants for various UART cards (already divided by 16 for divisor calculation) */

/* Texelec Commander X16 Serial Card: 921.6 kHz (14.7456 MHz / 16) */
#define TEXELEC_X16_UART_CLOCK 921600

/* Texelec Commander X16 Dual MIDI Card: 1 MHz (16 MHz / 16) */
#define TEXELEC_X16_DUAL_MIDI_UART_CLOCK 1000000

/* Default divisor for Dual MIDI at 31250 bps (MIDI standard): 1000000 / 31250 = 32 */
#define TEXELEC_X16_DUAL_MIDI_DEFAULT_DIVISOR 32

/* Standard baud rate constants */
#define BAUD_50     50
#define BAUD_300    300
#define BAUD_600    600
#define BAUD_1200   1200
#define BAUD_2400   2400
#define BAUD_4800   4800
#define BAUD_9600   9600
#define BAUD_19200  19200
#define BAUD_38400  38400
#define BAUD_57600  57600
#define BAUD_115200 115200
#define BAUD_230400 230400
#define BAUD_460800 460800
#define BAUD_921600 921600

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

/* Buffer Status Bitmap (in_buffer_status / out_buffer_status fields) */
#define BUF_EMPTY         0x01  /* Buffer is empty (head == tail) */
#define BUF_FULL          0x02  /* Buffer is full (head is one position before tail) */
#define BUF_WRAPPED       0x04  /* Pointer has wrapped around the circular buffer */

/**
 * Calculate UART divisor from crystal clock and desired baud rate
 * @param crystal_clock Crystal clock speed (already divided by 16)
 * @param baud_rate Desired baud rate
 * @return 16-bit divisor value (crystal_clock / baud_rate)
 */
unsigned int findDivisor(unsigned long crystal_clock, unsigned long baud_rate);

/**
 * Create and initialize a UART instance (calculates divisor from baud rate)
 * @param crystal_speed Crystal clock speed (already divided by 16)
 * @param baudrate Desired baud rate (numeric value, e.g., 9600, 115200)
 * @param base_address Base address of the UART hardware
 * @param databits Number of data bits (5, 6, 7, or 8)
 * @param parity Parity setting (PARITY_NONE, PARITY_ODD, or PARITY_EVEN)
 * @param stop_bits Number of stop bits (1 or 2)
 * @return Pointer to created UART_Instance, or NULL on failure
 */
UART_Instance* createUART(unsigned long crystal_speed, unsigned long baudrate, unsigned int base_address, unsigned char databits, Parity parity, unsigned char stop_bits);

/**
 * Create and initialize a UART instance (with explicit divisor)
 * @param crystal_speed Crystal clock speed (already divided by 16)
 * @param baudrate Desired baud rate (numeric value, e.g., 9600, 115200)
 * @param divisor Pre-calculated baud rate divisor
 * @param base_address Base address of the UART hardware
 * @param databits Number of data bits (5, 6, 7, or 8)
 * @param parity Parity setting (PARITY_NONE, PARITY_ODD, or PARITY_EVEN)
 * @param stop_bits Number of stop bits (1 or 2)
 * @return Pointer to created UART_Instance, or NULL on failure
 */
UART_Instance* createUARTWithDivisor(unsigned long crystal_speed, unsigned long baudrate, unsigned int divisor, unsigned int base_address, unsigned char databits, Parity parity, unsigned char stop_bits);

/**
 * Scan for UART devices at known base addresses
 * Tests the scratch register at each possible UART address from 0x9F60 to 0x9FF8
 * @param addresses Pointer to a buffer to store found UART addresses (at least 20 uint16_t entries)
 * @return Number of UARTs found
 */
unsigned char __fastcall__ scanUARTs(unsigned int *addresses);

/**
 * Global array of UART instance pointers
 * Each element points to a UART_Instance structure
 */
extern UART_Instance *uart_instances[MAX_UARTS];

/**
 * Current count of active UART instances
 */
extern unsigned char uart_instance_count;

/**
 * Flag indicating if custom IRQ handler is installed
 * 1 = IRQ handler active, 0 = not active
 */
extern unsigned char irq_handler_active;

/**
 * Library initialization routine
 * Call this once at program startup to initialize internal state
 * Clears UART instance count and IRQ handler flag
 */
void __fastcall__ _tl16c2550_init(void);

/**
 * Library test function
 * Adds 5 to the input value
 * @param value Input unsigned char value
 * @return value + 5
 */
unsigned char __fastcall__ libtest(unsigned char value);

/**
 * Add a UART instance to the global list and configure hardware
 * @param uart Pointer to UART_Instance to add
 * @return Index of added UART instance, or 0 on failure
 * this is a private function and does not need to be called publicly
 * its called by createUART and createUARTWithDivisor
 */
unsigned char __fastcall__ addUART(UART_Instance* uart);
#endif /* TL16C2550_H */
