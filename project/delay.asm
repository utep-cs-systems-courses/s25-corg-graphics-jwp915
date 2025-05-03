    .cdecls C,LIST,"msp430.h"
    .text
    .global delay_ms

delay_ms:
    ; Input: R12 = number of milliseconds
    ; Assume 1MHz clock = 1000 cycles per ms
    PUSH R14
    PUSH R15

1:  MOV #1000, R14
2:  DEC R14
    JNZ 2b
    DEC R12
    JNZ 1b

    POP R15
    POP R14
    RET
