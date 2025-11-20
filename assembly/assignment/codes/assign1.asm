; corrected 2-bit logic updater for 7474s
.include "/root/m328Pdef.inc"

.org 0x00
    rjmp RESET

RESET:
    ; Configure DDRD: PD2,PD3 inputs (0); PD4,PD5,PD6 outputs (1)
    ldi r16, 0b01110000    ; PD7 PD6 PD5 PD4 PD3 PD2 PD1 PD0
    out DDRD, r16

    ; Ensure PORTD bits for outputs are low initially
    ldi r16, 0x00
    out PORTD, r16

MAIN_LOOP:
    ; Read PIND - sample Q1 (PD2) and Q2 (PD3)
    in  r17, PIND          ; r17 holds PIND

    ; Extract Q1 into r20 (0 or 1)
    ldi r20, 0
    sbrc r17, 2            ; if PD2 set (Q1=1) skip next
    ldi r20, 1             ; NOTE: sbrc skips when bit is clear? check
    ; Alternative safe extraction:
    ; mov r20, r17
    ; andi r20, (1<<PD2)
    ; lsr r20 ; -> LSB = Q1

    ; Better, use explicit extraction to avoid confusion:
    mov r20, r17
    andi r20, 0b00000100   ; isolate PD2
    lsr r20                 ; shift so r20 bit0 = Q1
    lsr r20                 ; now r20 bit0 contains Q1 (two shifts because PD2 is bit2)

    ; Extract Q2 into r21 (0 or 1)
    mov r21, r17
    andi r21, 0b00001000   ; isolate PD3
    lsr r21
    lsr r21
    lsr r21                ; after 3 shifts, bit0 = original PD3
    ; (PD3 is bit3 -> shift right 3 times)

    ; Compute D1 = NOT(Q1) --> r24
    mov r24, r20
    com r24                ; bitwise NOT
    andi r24, 0x01         ; keep LSB only

    ; Compute D2 = Q1 XOR Q2 --> r25
    mov r25, r20
    eor r25, r21
    andi r25, 0x01

    ; Read PORTD, clear PD4 & PD5 bits, then set according to D1/D2
    in  r23, PORTD
    andi r23, 0b10001111   ; clear bits PD4(0x10) & PD5(0x20), keep others

    ; if D1 set, set PD4 (bit4)
    sbrc r24, 0
    ori r23, 0b00010000

    ; if D2 set, set PD5 (bit5)
    sbrc r25, 0
    ori r23, 0b00100000

    out PORTD, r23

    ; Pulse clock on PD6
    sbi PORTD, 6           ; PD6 high
    rcall DELAY
    cbi PORTD, 6           ; PD6 low
    rcall DELAY

    rjmp MAIN_LOOP

; Simple delay
DELAY:
    ldi r30, 0x05
DL1:
    ldi r31, 0xFF
DL2:
    ldi r26, 0xFF
DL3:
    dec r26
    brne DL3
    dec r31
    brne DL2
    dec r30
    brne DL1
    ret
