#include "sensors.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <MPU6050.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// Sensor objects
Adafruit_BMP280 bmp;
MPU6050 mpu;
TinyGPSPlus gps;
HardwareSerial gpsSerial(1);

void setupSensors() {
  Wire.begin();
  
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
    while (1);
  }

  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 not responding");
    while (1);
  }

  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
}

SensorData readSensors() {
  SensorData data;

  // BMP280
  data.temperature = bmp.readTemperature();
  data.pressure = bmp.readPressure() / 100.0F;

  // MPU6050
  mpu.getMotion6(&data.ax, &data.ay, &data.az, &data.gx, &data.gy, &data.gz);

  // GPS
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  data.latitude = gps.location.isValid() ? gps.location.lat() : 0.0;
  data.longitude = gps.location.isValid() ? gps.location.lng() : 0.0;
  data.speed = gps.speed.kmph();

  return data;
}
