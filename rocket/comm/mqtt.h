#pragma once
#include <PubSubClient.h>
void initMQTT();
void sendMQTT(const String &topic, const String &msg);
void mqttLoop();
