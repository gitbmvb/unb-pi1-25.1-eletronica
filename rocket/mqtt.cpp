#include "config.h"
#include "mqtt.h"
#include <WiFi.h>
#include <PubSubClient.h>

static WiFiClient wifiClient;
static PubSubClient mqttClient(wifiClient);

void initMQTT(){
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
}

void sendMQTT(const String &t, const String &m){
  if (!mqttClient.connected()){
    mqttClient.connect("ESP32Client");
  }
  if (mqttClient.connected()){
    mqttClient.publish(t.c_str(), m.c_str());
  }
}

void mqttLoop(){
  mqttClient.loop();
}
