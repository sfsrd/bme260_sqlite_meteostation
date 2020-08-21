
#ifndef MY_BME280_DRIVE_I2C_BME280RAWDATA_H
#define MY_BME280_DRIVE_I2C_BME280RAWDATA_H

#include <stdint.h>

class BME280RawData {
private:
    uint8_t pmsb;
    uint8_t plsb;
    uint8_t pxsb;

    uint8_t tmsb;
    uint8_t tlsb;
    uint8_t txsb;

    uint8_t hmsb;
    uint8_t hlsb;

    uint32_t temperature;
    uint32_t pressure;
    uint32_t humidity;
public:
    BME280RawData(uint8_t pmsb, uint8_t plsb, uint8_t pxsb, uint8_t tmsb, uint8_t tlsb, uint8_t txsb, uint8_t hmsb, uint8_t hlsb, uint32_t temperature, uint32_t pressure,
                  uint32_t humidity) {
        this->pmsb = pmsb;
        this->plsb = plsb;
        this->pxsb = pxsb;
        this->tmsb = tmsb;
        this->tlsb = tlsb;
        this->txsb = txsb;
        this->hmsb = hmsb;
        this->hlsb = hlsb;
        this->temperature = temperature;
        this->pressure = pressure;
        this->humidity = humidity;
    }

    BME280RawData() {
        this->pmsb = 0;
        this->plsb = 0;
        this->pxsb = 0;
        this->tmsb = 0;
        this->tlsb = 0;
        this->txsb = 0;
        this->hmsb = 0;
        this->hlsb = 0;
        this->temperature = 0;
        this->pressure = 0;
        this->humidity = 0;
    }

    virtual ~BME280RawData() {
    }

    uint32_t getPressure() {
        return pressure;
    }

    uint32_t getTemperature() {
        return temperature;
    }

    uint32_t getHumidity() {
        return humidity;
    }
};

#endif //MY_BME280_DRIVE_I2C_BME280RAWDATA_H