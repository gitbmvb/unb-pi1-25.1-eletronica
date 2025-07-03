#include "comms.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <BluetoothSerial.h>

// WiFi credentials
const char* ssid = "brunomartins";
const char* password = "314159265";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
BluetoothSerial BTSerial;

void setupCommunication() {
  // WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // MQTT
  client.setServer(mqtt_server, 1883);
  while (!client.connected()) {
    client.connect("ESP32Client");
    delay(500);
  }

  // Bluetooth
  BTSerial.begin("ESP32_BT");
}

void sendMQTT(const String& payload) {
  client.loop();
  if (!client.connected()) {
    client.connect("ESP32Client");
  }
  client.publish("unb/rockets/g1", payload.c_str());
}

void sendBluetooth(const String& payload) {
  BTSerial.println(payload);
}

String formatPayload(const SensorData& d) {
  String json = "{";
  json += "\"temperature\":" + String(d.temperature, 2) + ",";
  json += "\"pressure\":" + String(d.pressure, 2) + ",";
  json += "\"accel\":[" + String(d.ax) + "," + String(d.ay) + "," + String(d.az) + "],";
  json += "\"gyro\":[" + String(d.gx) + "," + String(d.gy) + "," + String(d.gz) + "],";
  json += "\"lat\":" + String(d.latitude, 6) + ",";
  json += "\"lng\":" + String(d.longitude, 6) + ",";
  json += "\"speed\":" + String(d.speed, 2);
  json += "}";
  return json;
}
