#include <Wire.h>
#include <MPU6050.h>
#include "mpu6050_sensor.h"

MPU6050 mpu;

void mpu6050_setup() {
  Wire.begin();
  mpu.initialize();
}

MPU6050Data mpu6050_read() {
  MPU6050Data data;
  data.accX = mpu.getAccelerationX() / 16384.0;
  data.accY = mpu.getAccelerationY() / 16384.0;
  data.accZ = mpu.getAccelerationZ() / 16384.0;
  data.gyroX = mpu.getRotationX() / 131.0;
  data.gyroY = mpu.getRotationY() / 131.0;
  data.gyroZ = mpu.getRotationZ() / 131.0;
  return data;
}
