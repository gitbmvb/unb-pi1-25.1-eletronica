#include <Adafruit_BMP280.h>
#include "bmp280_sensor.h"

Adafruit_BMP280 bmp;

void bmp280_setup() {
  bmp.begin(0x76);
}

BMP280Data bmp280_read() {
  BMP280Data data;
  data.temperature = bmp.readTemperature();
  data.pressure = bmp.readPressure() / 100.0;
  return data;
}
