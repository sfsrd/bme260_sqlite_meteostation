
#ifndef MY_BME280_DRIVE_I2C_BME280DATA_H
#define MY_BME280_DRIVE_I2C_BME280DATA_H

class BMP280Data {
private:
    double pressure;
    double temperature;
    double humidity;
    double altitude;
public:
    BMP280Data() {
        pressure = 0;
        temperature = 0;
        altitude = 0;
        humidity = 0;
    }
    BMP280Data(double pressure, double temperature, double humidity, double altitude) {
        this->pressure = pressure;
        this->temperature = temperature;
        this->humidity = humidity;
        this->altitude = altitude;
    }
    virtual ~BMP280Data() {
    }
    double getAltitude() {
        return altitude;
    }
    double getPressure() {
        return pressure;
    }
    double getTemperature() {
        return temperature;
    }
    double getHumidity() {
        return humidity;
    }
};

#endif //MY_BME280_DRIVE_I2C_BME280DATA_H