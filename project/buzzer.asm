    .text
    .global play_buzzer

play_buzzer:
    ; Plays a tone by toggling P2.1
    PUSH R4
    PUSH R5

    MOV #1000, R4           ; Duration loop
outer_loop:
    MOV #100, R5
toggle_loop:
    XOR #0x02, &P2OUT       ; Toggle BIT1 = 0x02 (buzzer)
    NOP
    NOP
    NOP
    NOP
    DEC R5
    JNZ toggle_loop

    DEC R4
    JNZ outer_loop

    BIC #0x02, &P2OUT       ; Turn buzzer OFF
    POP R5
    POP R4
    RET
