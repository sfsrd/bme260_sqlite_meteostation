#include <stdio.h>
#include <stdexcept>
#include <stdint.h>
#include <zconf.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <iostream>
#include <string>
#include <cstring>
#include "bme280.h"
#include "i2c_driver.h"
#include "sqlite3.h"
#include "date.h"
#include "database.h"

using namespace std::chrono;

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

std::string getCurrentDate(){
    std::string currentDate;
    currentDate = date::format("%F %T", time_point_cast<milliseconds>(system_clock::now()));
    return currentDate;
}

int main() {
    char *device = "/dev/i2c-1";
    int devId = BME280_I2C_ADDRESS;

    sqlite3* db;
    char *tableName = "Info_sensor";
    char *columns = "id INTEGER PRIMARY KEY AUTOINCREMENT, dt TEXT, temperature REAL, humidity REAL, pressure REAL";
    char qry[500];
    int rc;

    std::string currentDate;
    char cDate[100];

    database DB(db, "sensor_data.db");
    DB.openDB();
    DB.create_table(qry, tableName, columns);

   try {
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
             BMP280Data * bme280Data = bme280->getBMP280Data();
             printData(*bme280Data);
             currentDate = getCurrentDate();
             strcpy(cDate, currentDate.c_str());
             DB.generateQInsertData(qry, tableName, cDate, bme280Data->getTemperature(),bme280Data->getHumidity(),
                                    bme280Data->getPressure());
             std::cout<<"qry = "<< qry <<std::endl;
             rc = DB.insertQ(qry);
             std::cout<<"rc = "<< rc <<std::endl;
             sleep(5);
         }

     } catch (std::exception & e) {
         printf("%s\n", e.what());
     }

    DB.checkOK();
    DB.closeDB();
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
