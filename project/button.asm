    .text
    .global wait_for_press

wait_for_press:
    ; Returns 0 in R12 for valid press
    ; Returns 1 in R12 for too-early press
    PUSH R14

wait_loop:
    BIT #0x08, &P1IN        ; BIT3 = 0x08 (button input)
    JZ check_led
    JMP wait_loop

check_led:
    BIT #0x01, &P1OUT       ; BIT0 = 0x01 (LED output)
    JZ too_soon

    ; Debounce
    MOV #1000, R14
debounce_loop:
    DEC R14
    JNZ debounce_loop

    MOV #0, R12             ; Valid press
    POP R14
    RET

too_soon:
    MOV #1, R12             ; Too early
    POP R14
    RET
