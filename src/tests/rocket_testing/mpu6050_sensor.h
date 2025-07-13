#ifndef MPU6050_SENSOR_H
#define MPU6050_SENSOR_H

typedef struct {
  float accX, accY, accZ;
  float gyroX, gyroY, gyroZ;
} MPU6050Data;

void mpu6050_setup();
MPU6050Data mpu6050_read();

#endif
