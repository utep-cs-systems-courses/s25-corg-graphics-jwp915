#include <msp430.h>
#include "lcd.h"
#include <string.h>

// LCD Pins
#define LCD_RS BIT6  // P1.6
#define LCD_EN BIT7  // P1.7
#define LCD_D4 BIT4  // P1.4
#define LCD_D5 BIT5  // P1.5
#define LCD_D6 BIT2  // P1.2
#define LCD_D7 BIT3  // P1.3

#define LCD_CTRL (LCD_RS | LCD_EN)
#define LCD_DATA (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)

static void pulse_enable() {
    P1OUT |= LCD_EN;
    __delay_cycles(1000);
    P1OUT &= ~LCD_EN;
    __delay_cycles(1000);
}

static void send_nibble(unsigned char nibble) {
    P1OUT &= ~LCD_DATA;
    if (nibble & 0x01) P1OUT |= LCD_D4;
    if (nibble & 0x02) P1OUT |= LCD_D5;
    if (nibble & 0x04) P1OUT |= LCD_D6;
    if (nibble & 0x08) P1OUT |= LCD_D7;
    pulse_enable();
}

static void send_byte(unsigned char byte, int is_data) {
    if (is_data)
        P1OUT |= LCD_RS;
    else
        P1OUT &= ~LCD_RS;

    send_nibble(byte >> 4);
    send_nibble(byte & 0x0F);
    __delay_cycles(2000);
}

void lcd_command(unsigned char cmd) {
    send_byte(cmd, 0);
}

void lcd_data(unsigned char data) {
    send_byte(data, 1);
}

void lcd_init() {
    P1DIR |= LCD_CTRL | LCD_DATA;
    P1OUT &= ~(LCD_CTRL | LCD_DATA);

    __delay_cycles(15000);  // Wait for LCD power-up

    send_nibble(0x03);
    __delay_cycles(5000);
    send_nibble(0x03);
    __delay_cycles(200);
    send_nibble(0x03);
    send_nibble(0x02);  // Set 4-bit mode

    lcd_command(0x28); // 4-bit, 2-line, 5x8 dots
    lcd_command(0x0C); // Display ON, cursor OFF
    lcd_command(0x06); // Entry mode
    lcd_clear();
}

void lcd_clear() {
    lcd_command(0x01);
    __delay_cycles(2000);
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char pos = (row == 0) ? 0x80 : 0xC0;
    lcd_command(pos + col);
}

void lcd_print(const char *str) {
    while (*str)
        lcd_data(*str++);
}
