#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "config.h"
#include "mqtt_client.h"

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_setup() {
  client.setServer(MQTT_BROKER, MQTT_PORT);
}

void mqtt_loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      client.connect("ESP8266Client");
      delay(5000);
    }
  }
  client.loop();
}

void mqtt_publish(BMP280Data bmp, MPU6050Data mpu) {
  char payload[256];
  snprintf(payload, sizeof(payload),
    "{\"temperature\":%.2f,\"pressure\":%.2f,"
    "\"accX\":%.2f,\"accY\":%.2f,\"accZ\":%.2f,"
    "\"gyroX\":%.2f,\"gyroY\":%.2f,\"gyroZ\":%.2f}",
    bmp.temperature, bmp.pressure,
    mpu.accX, mpu.accY, mpu.accZ,
    mpu.gyroX, mpu.gyroY, mpu.gyroZ);

  client.publish(MQTT_TOPIC, payload);
}
