//
// Created by ariel on 8/14/20.
//

#ifndef BME280_I2C_DRIVER_H
#define BME280_I2C_DRIVER_H

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdint.h>
#include <string>

#define I2C_ADAPTER    "/dev/i2c-1"

class I2C_Driver{
private:
    int fd;
    std::string i2c_driver_id;

public:

    I2C_Driver(std::string i2c_driver_id);

    int write_buffer_i2c(uint8_t slave_addr, uint8_t reg, uint8_t data);

    int read_buffer_i2c(uint8_t slave_addr, uint8_t reg, int read_len, uint8_t read_res[]);

    int open_i2c_file();
};

#endif //BME280_I2C_DRIVER_H
