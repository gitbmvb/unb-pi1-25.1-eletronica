#ifndef COMMS_H
#define COMMS_H

#include "sensors.h"

void setupCommunication();
void sendMQTT(const String& payload);
void sendBluetooth(const String& payload);
String formatPayload(const SensorData& data);

#endif
