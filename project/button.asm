    .cdecls C,LIST,"msp430.h"
    .text
    .global wait_for_press

wait_for_press:
    ; Returns 0 in R12 if valid press
    ; Returns 1 in R12 if button was pressed too early (LED off)
    PUSH R14

wait_loop:
    BIT #BIT3, &P1IN      ; Check if button is pressed
    JZ check_led
    JMP wait_loop

check_led:
    BIT #BIT0, &P1OUT     ; Check if LED is ON
    JZ too_soon

    ; Debounce
    MOV #1000, R14
debounce_loop:
    DEC R14
    JNZ debounce_loop

    MOV #0, R12           ; Valid press
    POP R14
    RET

too_soon:
    MOV #1, R12           ; Too early
    POP R14
    RET
