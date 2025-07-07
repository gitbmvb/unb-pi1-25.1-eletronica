#include "config.h"
#include "sensors/bmp280.h"
#include "sensors/mpu6050.h"
#include "sensors/gps.h"
#include "comm/bluetooth.h"
#include "comm/mqtt.h"
#include <WiFi.h>

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  initBT();
  initMQTT();

  Serial.println(initBMP() ? "BMP OK" : "BMP FAIL");
  Serial.println(initMPU() ? "MPU OK" : "MPU FAIL");
  Serial.println(initGPS() ? "GPS OK" : "GPS FAIL");
}

void loop(){
  float temp, pres;
  MPUData mpu;
  GPSData gps;
  bool okBMP = readBMP(temp, pres);
  bool okMPU = readMPU(mpu);
  bool okGPS = readGPS(gps);

  String payload = "{";
  if (okBMP) payload += "\"T\":" + String(temp,2) + ",\"P\":" + String(pres,2) + ",";
  if (okMPU) payload += "\"ax\":" + String(mpu.ax,2) + ",\"ay\":" + String(mpu.ay,2) + ",\"az\":" + String(mpu.az,2) + ",";
  if (okMPU) payload += "\"gx\":" + String(mpu.gx,2) + ",\"gy\":" + String(mpu.gy,2) + ",\"gz\":" + String(mpu.gz,2) + ",";
  if (okGPS) payload += "\"lat\":" + String(gps.lat,6) + ",\"lng\":" + String(gps.lng,6) + ",";
  if (okGPS) payload += "\"alt\":" + String(gps.altitude,2) + ",\"spd\":" + String(gps.speed,2) + ",";
  if (payload.endsWith(",")) payload.remove(payload.length() - 1);
  payload += "}";

  Serial.println(payload);
  sendBT(payload);
  sendMQTT(MQTT_TOPIC, payload);
  mqttLoop();

  delay(2000);
}
