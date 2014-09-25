//Copyright (c) 2014, Giovanni Dante Grazioli (deroad)
#ifndef __LCD_I2C_H__
#define __LCD_I2C_H__

typedef unsigned char u8;
typedef struct _lcd{
   u8  dim;
   int dev;
}lcd;

void lcd_notify(lcd* l);
void lcd_cmd(lcd* l, u8 cmd);
void lcd_init(lcd* l, int dev);
void lcd_backlight(lcd* l);
void lcd_putc(lcd* l, u8 c);
void lcd_print(lcd* l, const char* t, u8 len, u8 line);
void lcd_clear(lcd* l);
void lcd_set_cursor(lcd* l, u8 col, u8 row);
/* not tested yet */
void lcd_add_char(lcd* l, const unsigned char font[8], u8 position);

#endif /*__LCD_I2C_H__*/

