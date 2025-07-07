#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include "bmp280_sensor.h"
#include "mpu6050_sensor.h"

void mqtt_setup();
void mqtt_loop();
void mqtt_publish(BMP280Data bmp, MPU6050Data mpu);

#endif
