//Copyright (c) 2014, Giovanni Dante Grazioli (deroad)
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "lcd.h"
#include "i2c.h"

void lcd_notify(lcd* l){
    assert(l);
    u8 v;
    get_i2c_data(l->dev, &v);
    set_i2c_data(l->dev, (v | 0x04) | 0x08);
    get_i2c_data(l->dev, &v);
    set_i2c_data(l->dev, (v & 0xFB) | 0x08);
}

void lcd_cmd(lcd* l, u8 cmd){
    assert(l);
    set_i2c_data(l->dev, (cmd & 0xF0)   | 0x08);
    lcd_notify(l);
    set_i2c_data(l->dev, (cmd & 0x0F)<<4| 0x08);
    lcd_notify(l);
    set_i2c_data(l->dev, 0x0 | 0x08);
}

void lcd_init(lcd* l, int dev){
    assert(l && dev > 0);
    l->dev = dev;
    l->dim = 0;
    set_i2c_data(l->dev, 0x30 | 0x08); // enable 8 bit mode
    lcd_notify(l);
    usleep(3);
    set_i2c_data(l->dev, 0x20 | 0x08); // enable 4 bit mode
    lcd_notify(l);
    usleep(3);
    lcd_notify(l);
    usleep(3);

    lcd_cmd(l, 0x28);
    lcd_cmd(l, 0x08);
    lcd_cmd(l, 0x01);
    lcd_cmd(l, 0x06);
    lcd_cmd(l, 0x0C);
    lcd_cmd(l, 0x0F);
}

void lcd_backlight(lcd* l){
    lcd_notify(l);
}

void lcd_putc(lcd* l, u8 c){
    assert(l);
    set_i2c_data(l->dev, 0x01 | (c & 0xF0)   | 0x08);
    lcd_notify(l);
    set_i2c_data(l->dev, 0x01 | (c & 0x0F)<<4| 0x08);
    lcd_notify(l);
    set_i2c_data(l->dev, 0x0 | 0x08);
}

void lcd_print(lcd* l, const char* t, u8 len, u8 line){
    assert(l && t && line < 4);
    u8 i;
	u8 rows[] = {0x00, 0x40, 0x14, 0x54};
    lcd_cmd(l, 0x80 | rows[line]);
    for(i=0; i<len; ++i)
        lcd_putc(l, t[i]);
    lcd_cmd(l, 0xC);
}

void lcd_clear(lcd* l){
    assert(l);
    lcd_cmd(l, 0x1);
    lcd_cmd(l, 0x2);
}

void lcd_set_cursor(lcd* l, u8 col, u8 row){
    assert(l && row < 4);
    u8 rows[] = {0x00, 0x40, 0x14, 0x54};
    lcd_cmd(l, 0x80 | (col + rows[row]));
}

void lcd_add_char(lcd* l, const unsigned char font[8], u8 position){
    u8 j;
    lcd_cmd(l, 0x40 | ((position & 7) << 3));
    for(j=0; j<8; ++j)
      lcd_putc(l, font[j]);
}


