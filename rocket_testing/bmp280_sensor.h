#ifndef BMP280_SENSOR_H
#define BMP280_SENSOR_H

typedef struct {
  float temperature;
  float pressure;
} BMP280Data;

void bmp280_setup();
BMP280Data bmp280_read();

#endif
