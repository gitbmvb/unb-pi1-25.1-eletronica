#include <ESP8266WiFi.h>
#include "config.h"

void setup_wifi() {
  delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
