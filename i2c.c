//Copyright (c) 2014, Giovanni Dante Grazioli (deroad)
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "i2c.h"

int open_i2c(const char* dev_path, unsigned char addr) {
    int dev;
    dev = open(dev_path, O_RDWR);

    ioctl(dev, I2C_SLAVE, addr & 0x7F);
    return dev;
}

void close_i2c(int dev) {
    close(dev);
}

int get_i2c_data(int dev, unsigned char *value) {
    int r;
    if((r = read(dev, value, 1))<0 ){
        printf("Failed to read from the i2c bus %d\n", r);
        return 1;
    }
    return 0;
}

int set_i2c_data(int dev, unsigned char val) {
    int r;
    unsigned char buf[2];
    buf[1] = 0;
    buf[0] = val;
    if((r = write(dev, buf, 1))<0 ){
        printf("Failed to write from the i2c bus %d\n", r);
        return 1;
    }
    usleep(2);
    return 0;
}

