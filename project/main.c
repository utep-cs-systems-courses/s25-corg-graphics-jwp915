#AiAnclude <msp430.h>
#include "lcd.h"

extern void delay_ms(unsigned int ms);    // From delay.asm
extern unsigned char wait_for_press();    // From button.asm
extern void play_buzzer();                // From buzzer.asm

void init_gpio() {
    WDTCTL = WDTPW | WDTHOLD;             // Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1DIR |= BIT0;                        // P1.0 LED output
    P1OUT &= ~BIT0;

    P1DIR &= ~BIT3;                       // P1.3 Button input
    P1REN |= BIT3;
    P1OUT |= BIT3;

    P2DIR |= BIT1;                        // P2.1 Buzzer output
    P2OUT &= ~BIT1;
}

int main(void) {
    init_gpio();
    lcd_init();
    lcd_clear();

    while (1) {
        lcd_set_cursor(0, 0);
        lcd_print("Wait for LED...");
        delay_ms(1000 + (rand() % 3000));

        P1OUT |= BIT0;                    // LED ON
        unsigned long start = TAR;        // Capture start time
        lcd_clear();
        lcd_print("Press now!");

        unsigned char result = wait_for_press();
        P1OUT &= ~BIT0;                   // LED OFF

        if (result == 1) {
            lcd_clear();
            lcd_print("Too Soon!");
            play_buzzer();               // Signal failure
        } else {
            unsigned long end = TAR;
            unsigned int reaction_time = (end - start) / 8; // Approx. ms
            char buffer[16];
            lcd_clear();
            sprintf(buffer, "Time: %d ms", reaction_time);
            lcd_print(buffer);
            play_buzzer();               // Signal success
        }

        delay_ms(2000);
        lcd_clear();
    }
}
