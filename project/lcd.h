#ifndef LCD_H
#define LCD_H

void lcd_init();
void lcd_clear();
void lcd_set_cursor(unsigned char row, unsigned char col);
void lcd_print(const char *str);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);

#endif
