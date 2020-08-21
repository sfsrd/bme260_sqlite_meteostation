cmake_minimum_required(VERSION 3.13)
project(bme280)

set(CMAKE_CXX_STANDARD 14)

add_executable(bme280 main.cpp bme280.cpp bme280.h BME280CalibrationData.h BME280Data.h BME280RawData.h i2c_driver.cpp i2c_driver.h)
target_link_libraries(bme280 LINK_PUBLIC sqlite3)