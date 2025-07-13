#include "sensors.h"
#include "comms.h"

void setup() {
  Serial.begin(115200);
  setupSensors();
  setupCommunication();
}

void loop() {
  SensorData data = readSensors();
  String payload = formatPayload(data);
  sendMQTT(payload);
  // sendBluetooth(payload);
  Serial.println(payload);
  delay(1000);
}
