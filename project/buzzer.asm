    .cdecls C,LIST,"msp430.h"
    .text
    .global play_buzzer

play_buzzer:
    ; Plays a square wave tone on P2.1 for a short duration
    ; Assumes 1 MHz clock

    PUSH R4
    PUSH R5

    MOV #1000, R4         ; Outer loop: total duration
outer_loop:
    MOV #100, R5          ; Inner loop: one cycle
toggle_loop:
    XOR #BIT1, &P2OUT     ; Toggle P2.1
    NOP
    NOP
    NOP
    NOP
    DEC R5
    JNZ toggle_loop

    DEC R4
    JNZ outer_loop

    BIC #BIT1, &P2OUT     ; Ensure buzzer is OFF
    POP R5
    POP R4
    RET
