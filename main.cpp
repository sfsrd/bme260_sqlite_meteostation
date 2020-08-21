#include <stdio.h>
#include <stdexcept>
#include <stdint.h>
#include <zconf.h>
#include <iostream>
#include "bme280.h"
#include "i2c_driver.h"
#include "sqlite3.h"
#include <ctime>
#include <iomanip>

int i2c_init();
int i2c_read(uint8_t reg, int read_len, uint8_t read_res[]);
int i2c_write(uint8_t reg, uint8_t data);

I2C_Driver *i2c_driver = new I2C_Driver(I2C_ADAPTER);

void printData(BMP280Data bme280Data){
    std::cout <<"Temperature: " << bme280Data.getTemperature() << std::endl;
    std::cout <<"Pressure: " << bme280Data.getPressure() << std::endl;
    std::cout <<"Humidity: " << bme280Data.getHumidity() << std::endl;
    std::cout <<"- - -" << std::endl;
};

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    char *device = "/dev/i2c-1";
    int devId = BME280_I2C_ADDRESS;
    std::string currentTime;

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char qry[80];

    //TABLE Info (temperature REAL, humidity REAL, pressure REAL)

    char *sqlCreate = "CREATE TABLE Info (temperature REAL, humidity REAL, pressure REAL, date d, time t);";
    char *sqlDropTable = "DROP TABLE Info";
    char *sqlShow = "SELECT * FROM Info;";

    rc = sqlite3_open("sensor_data.db", &db);
    rc = sqlite3_exec(db, sqlShow, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);

    /*try {
        BME280 * bme280 = new BME280(device, devId, i2c_init, i2c_read, i2c_write);
        int fd = bme280->init();
        bme280->reset();

        if (fd < 0) {
            printf("Device not found");
            return -1;
        }

        bme280->reset();
        bme280->setPowerMode(BME280_NORMAL_MODE);
        bme280->setTemperatureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_TEMPERATURE);
        bme280->setPressureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_PRESSURE);
        bme280->setHumidityOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_HUMIDITY);

        while (true) {
            rc = sqlite3_open("sensor_data.db", &db);
            std::cout<<"time&date = "<< currentTime <<std::endl;
            BMP280Data * bme280Data = bme280->getBMP280Data();
            printData(*bme280Data);

            sprintf(qry,"INSERT INTO Info values(%.2f, %.2f, %.2f, date('now'), time('now'));", bme280Data->getTemperature(),bme280Data->getHumidity(),
                     bme280Data->getPressure());
            std::cout<<"qry = "<< qry <<std::endl;
            rc = sqlite3_exec(db, qry, callback, 0, &zErrMsg);
            if( rc != SQLITE_OK ) {
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
            } else {
                fprintf(stdout, "Operation done successfully\n");
            }
            sqlite3_close(db);
            sleep(5);
        }

    } catch (std::exception & e) {
        printf("%s\n", e.what());
    }*/

    return 0;
}


int i2c_init() {
    return i2c_driver->open_i2c_file();
}

int i2c_read(uint8_t reg, int read_len, uint8_t read_res[]){
    return i2c_driver->read_buffer_i2c(BME280_ADDRESS, reg, read_len, read_res);
}

int i2c_write(uint8_t reg, uint8_t data) {
    return i2c_driver->write_buffer_i2c(BME280_ADDRESS, reg, data);
}