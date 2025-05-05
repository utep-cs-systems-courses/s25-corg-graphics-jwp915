    .text
    .global delay_ms

delay_ms:
    ; Input: R12 = number of milliseconds
    PUSH R14
    PUSH R15

outer_loop:
    MOV #1000, R14         ; 1ms at ~1MHz
inner_loop:
    DEC R14
    JNZ inner_loop
    DEC R12
    JNZ outer_loop

    POP R15
    POP R14
    RET
