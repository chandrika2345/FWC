.include "/root/m328Pdef.inc"

.org 0x00
    rjmp RESET

; ===== Reset Routine =====
RESET:
    ; Set PD2–PD7 as output
    ldi r16, 0b11111100
    out DDRD, r16
    ; Set PB0 as output
    sbi DDRB, 0

    ; Load Z-pointer with start of pattern table
    ldi ZH, high(SEG_TABLE << 1)
    ldi ZL, low(SEG_TABLE << 1)

MAIN_LOOP:
    ; Load pattern for PORTD
    lpm r16, Z+
    ; Load pattern for PORTB
    lpm r17, Z+

    ; Output to ports
    out PORTD, r16
    out PORTB, r17

    rcall DELAY

    ; Check if reached end of table (10 numbers)
    cpi ZL, low(SEG_TABLE_END << 1)
    brne MAIN_LOOP

    ; Reset Z-pointer
    ldi ZH, high(SEG_TABLE << 1)
    ldi ZL, low(SEG_TABLE << 1)
    rjmp MAIN_LOOP

; ===== Delay Routine =====
DELAY:
    ldi r18, 50       ; Outer loop count
DL1:
    ldi r19, 255
DL2:
    ldi r20, 255
DL3:
    dec r20
    brne DL3
    dec r19
    brne DL2
    dec r18
    brne DL1
    ret

; ===== Segment Patterns for Common Anode (Active Low) =====
; Order: PORTD pattern, PORTB pattern
; PD2=A, PD3=B, PD4=C, PD5=D, PD6=E, PD7=F, PB0=G
; 0 = A,B,C,D,E,F ON (0), G OFF (1)

SEG_TABLE:
    .DB 0b00000000, 0b00000001   ; 0
    .DB 0b11100100, 0b00000001   ; 1
    .DB 0b10010000, 0b00000000   ; 2
    .DB 0b11000000, 0b00000000   ; 3
    .DB 0b01100100, 0b00000000   ; 4
    .DB 0b01001000, 0b00000000   ; 5
    .DB 0b00001000, 0b00000000   ; 6
    .DB 0b11100000, 0b00000001   ; 7
    .DB 0b00000000, 0b00000000   ; 8
    .DB 0b01000000, 0b00000000   ; 9
SEG_TABLE_END:
