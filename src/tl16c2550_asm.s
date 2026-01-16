; tl16c2550_asm.s
; Low-level assembly routines for TL16C2550 UART
; Optimized for 65C02 processor in Commander X16

.export _uart_putc_fast
.export _uart_getc_fast

.include "tl16c2550.inc"

.segment "CODE"

;---------------------------------------------------------------------------
; Fast character output routine
; void __fastcall__ uart_putc_fast(char c);
; Input: A = character to send
; Note: Uses UART_BASE_A (hardcoded for performance)
;---------------------------------------------------------------------------
.proc _uart_putc_fast
    pha                     ; Save character
    
@wait:
    lda UART_BASE_A + UART_LSR  ; Read LSR (Line Status Register)
    and #LSR_THR_EMPTY          ; Check THR empty bit
    beq @wait                   ; Wait if not ready
    
    pla                         ; Restore character
    sta UART_BASE_A + UART_THR  ; Write to THR
    rts
.endproc

;---------------------------------------------------------------------------
; Fast character input routine
; char __fastcall__ uart_getc_fast(void);
; Output: A = received character
;---------------------------------------------------------------------------
.proc _uart_getc_fast
@wait:
    lda UART_BASE_A + UART_LSR  ; Read LSR
    and #LSR_DATA_READY         ; Check data ready bit
    beq @wait                   ; Wait if no data
    
    lda UART_BASE_A + UART_RBR  ; Read RBR
    rts
.endproc
