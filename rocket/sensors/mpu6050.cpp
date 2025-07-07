#include "mpu6050.h"
#include <Adafruit_MPU6050.h>
#include <Wire.h>

TwoWire WireMPU = TwoWire(1);
static Adafruit_MPU6050 mpu;

bool initMPU(){
  WireMPU.begin(MPU_SDA, MPU_SCL);
  return mpu.begin(&WireMPU);
}

bool readMPU(MPUData &d){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  d = {a.acceleration.x, a.acceleration.y, a.acceleration.z,
       g.gyro.x, g.gyro.y, g.gyro.z, temp.temperature};
  return true;
}
