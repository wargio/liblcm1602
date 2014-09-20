//Copyright (c) 2014, Giovanni Dante Grazioli (deroad)
#ifndef __I2C_H__
#define __I2C_H__

#define I2C_OK                0
#define I2C_ERROR             1

int open_i2c(const char* dev_path, unsigned char addr);
void close_i2c(int dev);
int set_i2c_data(int dev, unsigned char val);
int get_i2c_data(int dev, unsigned char *value);

#endif
