#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "i2c.h"
#include "lcd.h"

#define I2C_FILE_NAME "/dev/i2c-0"

char* txt = "be happy"; 

int main(){
    int i2c_dev;
    unsigned int i, j, dir;
    lcd lcd0;
    // 0x27 is the address of the i2c device
    i2c_dev = open_i2c(I2C_FILE_NAME, 0x27);
    if(i2c_dev <0){
       printf("Errore: %d\n", i2c_dev);
       return 1;
    }
    char tmp[16];
    dir = 0;
    i=0;
    lcd_init(&lcd0, i2c_dev);
    while(i < 0xffffffff){
       j = i%13;
       memset(tmp, ' ', 16);
       if(j == 0) dir = !dir;
       if(dir){
           tmp[j]='^';
           tmp[j+1]='_';
           tmp[j+2]='^';
       }else{
           tmp[15-j]='^';
           tmp[14-j]='_';
           tmp[13-j]='^';
       }
       lcd_clear(&lcd0);
       lcd_print(&lcd0, txt, 8, 0);
       lcd_print(&lcd0, tmp, 16, 1);
       usleep(100000);
       ++i;
    }
    close_i2c(i2c_dev);
    return 0;
}
