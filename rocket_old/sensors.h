#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>

struct SensorData {
  float temperature;
  float pressure;
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  float latitude;
  float longitude;
  float speed;
};

void setupSensors();
SensorData readSensors();

#endif
