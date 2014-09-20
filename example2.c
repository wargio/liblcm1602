#include <stdio.h>
#include <string.h>
#include "i2c.h"
#include "lcd.h"

#define I2C_FILE_NAME                "/dev/i2c-0"
int main(int argc, char **argv){
    int i2c_dev, i;
    lcd lcd0;
    i2c_dev = open_i2c(I2C_FILE_NAME, 0x27);
    if(i2c_dev <0){
       printf("Errore: %d\n", i2c_dev);
       return 1;
    }
    lcd_init(&lcd0, i2c_dev);//, 16);
    lcd_clear(&lcd0);
    for(i=1; i<3 && i<argc; ++i)
        lcd_print(&lcd0, argv[i], strlen(argv[i]), i-1);
    
    close_i2c(i2c_dev);
    return 0;
}
