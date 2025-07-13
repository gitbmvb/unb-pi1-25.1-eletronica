#include "config.h"
#include "wifi_client.h"
#include "mqtt_client.h"
#include "bmp280_sensor.h"
#include "mpu6050_sensor.h"

void setup() {
  Serial.begin(115200);
  setup_wifi();
  mqtt_setup();
  bmp280_setup();
  mpu6050_setup();
}

void loop() {
  mqtt_loop();

  BMP280Data bmp = bmp280_read();
  MPU6050Data mpu = mpu6050_read();

  mqtt_publish(bmp, mpu);

  delay(5000);
}
