; tl16c2550.inc
; Assembly include file for TL16C2550 UART constants

; UART Base Addresses
UART_BASE = $9F60


; UART Address Offset
UART_OFFSETS = $08       ; Offset between UART addresses (8 bytes)

; UART_Instance Structure Offsets
UART_INST_BASE_ADDRESS    = 0  ; Base address of the UART (2 bytes)
UART_INST_INPUT_BUFFER    = 2  ; Pointer to input buffer (2 bytes)
UART_INST_IN_BUF_STATUS   = 4  ; Input buffer status (1 byte)
UART_INST_OUTPUT_BUFFER   = 5  ; Pointer to output buffer (2 bytes)
UART_INST_OUT_BUF_STATUS  = 7  ; Output buffer status (1 byte)
UART_INST_INPUT_HEAD      = 8  ; Input buffer head offset (1 byte)
UART_INST_INPUT_TAIL      = 9  ; Input buffer tail offset (1 byte)
UART_INST_OUTPUT_HEAD     = 10 ; Output buffer head offset (1 byte)
UART_INST_OUTPUT_TAIL     = 11 ; Output buffer tail offset (1 byte)
UART_INST_CRYSTAL_SPEED   = 12 ; Crystal clock speed / 16 (4 bytes)
UART_INST_DIVISOR         = 16 ; Baud rate divisor (2 bytes)
UART_INST_BAUDRATE        = 18 ; Current baud rate setting (1 byte)
UART_INST_CUSTOM_BAUDRATE = 19 ; Custom baud rate value (2 bytes)
UART_INST_LCR             = 21 ; Line Control Register (1 byte)
UART_INST_SIZE            = 22 ; Total size of UART_Instance structure

; Buffer Status Bitmap (in_buffer_status / out_buffer_status fields)
BUF_EMPTY                 = $01 ; Bit 0: Buffer is empty (head == tail)
BUF_FULL                  = $02 ; Bit 1: Buffer is full (head is one position before tail)
BUF_WRAPPED               = $04 ; Bit 2: Pointer has wrapped around the circular buffer

; Register Offsets
UART_RBR = 0    ; Receiver Buffer Register (read)
UART_THR = 0    ; Transmitter Holding Register (write)
UART_IER = 1    ; Interrupt Enable Register
UART_IIR = 2    ; Interrupt Identification Register (read)
UART_FCR = 2    ; FIFO Control Register (write)
UART_LCR = 3    ; Line Control Register
UART_MCR = 4    ; Modem Control Register
UART_LSR = 5    ; Line Status Register
UART_MSR = 6    ; Modem Status Register
UART_SCR = 7    ; Scratch Register
UART_DLL = 0   ; Divisor Latch Low Byte (when DLAB=1)
UART_DLM = 1   ; Divisor Latch High Byte (when DLAB=1)

; Line Status Register Bits
LSR_DATA_READY  = $01 ; Bit 0: Receiver data ready (data available to read)
LSR_OVERRUN_ERR = $02 ; Bit 1: Overrun error (data lost, new data received before previous was read)
LSR_PARITY_ERR  = $04 ; Bit 2: Parity error (received data has incorrect parity)
LSR_FRAMING_ERR = $08 ; Bit 3: Framing error (stop bit not detected)
LSR_BREAK_INT   = $10 ; Bit 4: Break interrupt (receiver input held low for >1 character period)
LSR_THR_EMPTY   = $20 ; Bit 5: Transmitter Holding Register empty (ready for next byte)
LSR_TX_EMPTY    = $40 ; Bit 6: Transmitter empty (both THR and shift register empty)
LSR_FIFO_ERR    = $80 ; Bit 7: FIFO error (parity/framing/break error in FIFO)

; Commander X16 System Vectors
IRQ_VECTOR      = $0314 ; IRQ vector address (low byte at $0314, high byte at $0315)

