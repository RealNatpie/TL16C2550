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
;        X/Y = uart_base (low/high)
;---------------------------------------------------------------------------
.proc _uart_putc_fast
    pha                     ; Save character
    
@wait:
    lda UART_BASE_A + 5     ; Read LSR (Line Status Register)
    and #$20                ; Check THR empty bit
    beq @wait               ; Wait if not ready
    
    pla                     ; Restore character
    sta UART_BASE_A         ; Write to THR
    rts
.endproc

;---------------------------------------------------------------------------
; Fast character input routine
; char __fastcall__ uart_getc_fast(void);
; Output: A = received character
;---------------------------------------------------------------------------
.proc _uart_getc_fast
@wait:
    lda UART_BASE_A + 5     ; Read LSR
    and #$01                ; Check data ready bit
    beq @wait               ; Wait if no data
    
    lda UART_BASE_A         ; Read RBR
    rts
.endproc
