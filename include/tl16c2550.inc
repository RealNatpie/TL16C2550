; tl16c2550.inc
; Assembly include file for TL16C2550 UART constants

; UART Base Addresses
UART_BASE_A = $9F60
UART_BASE_B = $9F68

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

; Line Status Register Bits
LSR_DATA_READY  = $01
LSR_OVERRUN_ERR = $02
LSR_PARITY_ERR  = $04
LSR_FRAMING_ERR = $08
LSR_BREAK_INT   = $10
LSR_THR_EMPTY   = $20
LSR_TX_EMPTY    = $40
LSR_FIFO_ERR    = $80
