#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "lcd.h"

#define I2C_FILE_NAME "/dev/i2c-0"

const char* txt[]  = {
    "I work on the PI",
    "via liblcm1602.a"
};

int main(){
    int i2c_dev;
    lcd lcd0;
    // 0x27 is the address of the i2c device
    i2c_dev = open_i2c(I2C_FILE_NAME, 0x27);
    if(i2c_dev <0){
       printf("Errore: %d\n", i2c_dev);
       return 1;
    }
    lcd_init(&lcd0, i2c_dev);
    lcd_clear(&lcd0);
    lcd_print(&lcd0, txt[0], strlen(txt[0]), 0);
    lcd_print(&lcd0, txt[1], strlen(txt[1]), 1);
    close_i2c(i2c_dev);
    return 0;
}
