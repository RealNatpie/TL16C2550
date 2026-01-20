; tl16c2550_asm.s
; Low-level assembly routines for TL16C2550 UART
; Optimized for 65C02 processor in Commander X16

;---------------------------------------------------------------------------
; Exported functions (available to C code)
;---------------------------------------------------------------------------

.export _scanUARTs          ; Scan for UART devices
.export _libtest            ; Library test function
.export _addUART            ; Add a UART instance to the global list
.export _tl16c2550_init     ; Startup initialization routine
;---------------------------------------------------------------------------
; Imported variables (defined in C, used in assembly)
;---------------------------------------------------------------------------
.include "zeropage.inc"
.include "tl16c2550.inc"
.include "cx16.inc"
; Zero page pointers for the IRQ handler
.zeropage
_uartPointer:  .res 2        ; Temporary pointer (2 bytes) for IRQ hardware access.
_uartAddress:  .res 2        ; Temporary storage for UART base address (2 bytes).
_uartStringP1: .res 2        ; String Pointer1 for IRQ handler use
_uartStringP2: .res 2        ; String Pointer2 for IRQ handler use
.segment "CODE"

;---------------------------------------------------------------------------
; Scan for UART devices by testing scratch register
; uint8_t __fastcall__ scanUARTs(uint16_t *addresses);
; Input: AX = pointer to address buffer (A=low byte, X=high byte)
; Output: A = number of UARTs found
; Destroys: All registers
;---------------------------------------------------------------------------
.proc _scanUARTs
    sta ptr1            ; Store buffer pointer (low byte in ptr1)
    stx ptr1+1          ; Store buffer pointer (high byte in ptr1+1)
    
    lda #<UART_BASE     ; Start address low byte
    sta ptr2            ; Store in address working variable (zero page pointer)
    lda #>UART_BASE     ; Start address high byte
    sta ptr2+1          ; Store in address working variable (zero page pointer)
    
    stz tmp1            ; Initialize found count (tmp1) to 0
    
    lda #20             ; Loop 20 times (addresses from 9F60 to 9FF8)
    sta tmp2            ; Initialize loop counter (tmp2)
    
@scan_loop:
 
    ; Write test value to scratch register (offset 7)
    lda #$A5            ; Test pattern (10100101)
    ldy #7              ; Offset to scratch register
    sta (ptr2),y        ; Write test value to scratch register
    
    ; Read back and verify
    lda (ptr2),y        ; Read scratch register
    cmp #$A5            ; Compare with test pattern
    bne @skip_address   ; If not equal, skip this address
    
    ; Found a UART! Store the address
   
    
    lda tmp1     ; Get current found count (tmp1)
    asl                 ; Multiply by 2 for 16-bit address storage
    tay                 ; Use as index into buffer
    
    lda ptr2            ; Get low byte of address
    sta (ptr1),y        ; Store in buffer
    
    iny                 ; Move to next position
    lda ptr2+1          ; Get high byte of address
    sta (ptr1),y        ; Store in buffer
    
    inc tmp1     ; Increment found count (tmp1)
    
@skip_address:
    ; Move to next address (add UART_OFFSET)
    lda ptr2
    clc
    adc #UART_OFFSETS    ; Add offset (0x08)
    sta ptr2
    
    dec tmp2      ; Decrement loop counter (tmp2)
    beq @done           ; Short branch if done
    jmp @scan_loop      ; Jump back (too far for short branch)
    
@done:    
    lda tmp1     ; Return the count of found UARTs (tmp1)
    ldx #0              ; Clear X register
    rts
.endproc

;---------------------------------------------------------------------------
; Library test function
; uint8_t __fastcall__ libtest(uint8_t value);
; Input: A = unsigned char value
; Output: A = value + 5
; Destroys: A, X
;---------------------------------------------------------------------------
.proc _libtest
    clc                 ; Clear carry for addition
    adc #$05            ; Add 5 to input value
    ldx #0              ; Clear X register (cc65 convention for char return)
    rts
.endproc

;---------------------------------------------------------------------------
; Library initialization routine (called once at startup)
; void __fastcall__ _tl16c2550_init(void);
; Input: None
; Output: A = 0 if successful, non-zero if IRQ vector is corrupted
; Destroys: A, X, Y
;---------------------------------------------------------------------------
.proc _tl16c2550_init
    ; Initialize UART instance count to zero
    stz _uart_instance_count
    stz _irq_handler_active
    
    rts
.endproc

;---------------------------------------------------------------------------
; Install custom IRQ handler
; Saves the current IRQ vector and installs our handler
; Input: None
; Output: None
; Destroys: A
;---------------------------------------------------------------------------
addIRQ:
    ; Save the current IRQ vector so we can chain to it later
    lda IRQ_VECTOR              ; Load low byte of current IRQ handler
    sta default_irq_vector      ; Store it for later
    lda IRQ_VECTOR+1            ; Load high byte of current IRQ handler
    sta default_irq_vector+1    ; Store it for later
    
    ; Install our custom IRQ handler
    sei                         ; Disable interrupts while modifying vector
    lda #<irqHandler            ; Load low byte of our handler address
    sta IRQ_VECTOR              ; Store it in the IRQ vector
    lda #>irqHandler            ; Load high byte of our handler address
    sta IRQ_VECTOR+1            ; Store it in the IRQ vector
    lda #1                      ; Set flag to indicate handler is active
    sta _irq_handler_active     ; Store the flag
    cli                         ; Re-enable interrupts
    rts

;---------------------------------------------------------------------------
; Restore original IRQ handler
; Restores the IRQ vector that was saved by addIRQ
; Input: None
; Output: None
; Destroys: A
;---------------------------------------------------------------------------
restoreIRQ:
    sei                         ; Disable interrupts while modifying vector
    lda default_irq_vector      ; Load low byte of saved IRQ handler
    sta IRQ_VECTOR              ; Restore it to the IRQ vector
    lda default_irq_vector+1    ; Load high byte of saved IRQ handler
    sta IRQ_VECTOR+1            ; Restore it to the IRQ vector
    stz _irq_handler_active     ; Clear flag (store zero) - handler not active
    cli                         ; Re-enable interrupts
    rts

;---------------------------------------------------------------------------
; Custom IRQ handler
; This is called when any hardware interrupt occurs
; Currently just chains to the original handler (placeholder)
; Note: Registers (A,X,Y) are already saved by KERNAL before we get here
;---------------------------------------------------------------------------
irqHandler:
    ; TODO: Check UART IIR registers to see if UART caused the interrupt
    ; TODO: If UART interrupt, handle it (read/write data to buffers)
    ; Chain to the original IRQ handler to process other interrupt sources
    ; There are 3 pointers resrved for use exclusivly in the interupt handler
    ; _uartPointer - used to point to the UART being serviced
    ; _uartAddress - used to store the base address of the UART being serviced
    ; _uartIndexPntr - used to index into the uart_instances array
    ;  but now that I think about it I don't know that I need the instance array, I may
    ; have been smoking crack when I made that decision.   I'm going to store the base address
    ;  in _uartAddress and work from there.   So I only need _uartPointer and _uartAddress
    ;  just thinking outloud here.   
    jmp (default_irq_vector)


;---------------------------------------------------------------------------
; Add a UART instance to the global UART instances array
; uint8_t __fastcall__ addUART(UART_Instance *uart);
; Input: AX = pointer to UART_Instance (A=low byte, X=high byte)
; Output: A = 1 if successful, 0 if array is full
; Destroys: A, X, Y
;---------------------------------------------------------------------------
.proc _addUART
    sta tmp1                        ; Store UART_Instance pointer (low byte)
    stx tmp2                        ; Store UART_Instance pointer (high byte)
    
    lda _uart_instance_count
    cmp #20
    bcc @continue                   ; If less than 20, continue
    jmp @full                       ; Jump to failure (can reach far away)
@continue:
    
    lda #<_uart_instances
    sta ptr1                        ; Load UART instances array base address (low byte)
    lda #>_uart_instances
    sta ptr1+1                      ; Load UART instances array base address (high byte)
    
    lda _uart_instance_count
    asl                             ; Multiply count by 2 for 16-bit pointer storage
    tay                             ; Use as index into array
    
    sei                             ; Disable interrupts while modifying shared data
    lda tmp1
    sta (ptr1),y                    ; Store UART_Instance pointer (low byte)
    iny                             ; Move to high byte 
    lda tmp2                        ; Get high byte of UART_Instance pointer
    sta (ptr1),y                    ; Store UART_Instance pointer (high byte)
    
    ; Increment the UART instance count
    lda _uart_instance_count
    inc
    sta _uart_instance_count
    cli                             ; Re-enable interrupts
    
  
    
    ; Install IRQ handler if not already running
    lda _irq_handler_active
    bne @irq_running
    jsr addIRQ
@irq_running:   
    lda tmp1
    sta ptr1                        ; Setup pointer to UART_Instance (low byte)
    lda tmp2
    sta ptr1+1                      ; Setup pointer to UART_Instance (high byte)
    
    ; Get UART base address from UART_Instance
    ldy #UART_INST_BASE_ADDRESS
    lda (ptr1),y
    sta ptr2                        ; Store UART base address (low byte)
    iny
    lda (ptr1),y
    sta ptr2+1                      ; Store UART base address (high byte)
    
    ;- ---------------------------------------------------------------------------
    ; ptr1 = UART_Instance pointer
    ; ptr2 = UART base address
    ; ---------------------------------------------------------------------------

    ; Get divisor from UART_Instance
    ldy #UART_INST_DIVISOR
    lda (ptr1),y    ; Get divisor (low byte)
    sta tmp3                        ; Store divisor (low byte)
    iny
    lda (ptr1),y    ; Get divisor (high byte)
    sta tmp4                        ; Store divisor (high byte)
    sei                             ; Disable interrupts while configuring UART
    ; Set DLAB to access divisor registers
    ldy #UART_LCR
    lda (ptr2),y
    ora #$80                        ; Set DLAB bit
    sta (ptr2),y
    
    ; Write divisor
    ldy #UART_DLL
    lda tmp3
    sta (ptr2),y                    ; Write Divisor Latch Low Byte
    iny
    lda tmp4
    sta (ptr2),y                    ; Write Divisor Latch High Byte
    
    ; Clear DLAB to access normal registers
    ldy #UART_LCR
    lda (ptr2),y
    and #$7F                        ; Clear DLAB bit
    sta (ptr2),y

    ; copy LCR settings from UART_Instance to UART hardware
    ldy #UART_INST_LCR
    lda (ptr1),y                    ; Get LCR from UART_Instance
    ldy #UART_LCR
    sta (ptr2),y                    ; Set Line Control Register on hardware

    
    
    cli                             ; Re-enable interrupts
    ; Return success
    lda _uart_instance_count        ; Return return count as index (success)
    ldx #0
    rts
    
@full:
    lda #0                          ; Return 0 (failure - array full)
    ldx #0
    rts
.endproc

;---------------------------------------------------------------------------
; Working variables for UART scanning
;---------------------------------------------------------------------------
.segment "DATA"

.export _irq_handler_active
.export _uart_instances
.export _uart_instance_count

default_irq_vector: .word 0     ; Storage for the default IRQ vector
_irq_handler_active: .byte 0    ; Flag: 1 if IRQ handler is active, 0 if not

; Array of pointers to UART_Instance structures (20 entries, 2 bytes each = 40 bytes total)
_uart_instances: .res 40        ; Reserve 40 bytes for 20 UART instance pointers

; Count of active UART instances
_uart_instance_count: .byte 0   ; Current number of initialized UARTs

