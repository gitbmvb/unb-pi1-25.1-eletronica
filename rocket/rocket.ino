#include <TinyGPS++.h>

TinyGPSPlus gps;

// Use the ESP8266 Hardware Serial for GPS, e.g. Serial1
// If using NodeMCU or Wemos D1 mini, Serial1 is RX only on GPIO3
// For 5Hz, your GPS must be set accordingly outside this code

void setup() {
  Serial.begin(115200);      // Serial monitor output
  Serial1.begin(9600);       // GPS module serial (default 9600 baud)
  Serial.println("GPS 5Hz reading started");
}

void loop() {
  while (Serial1.available() > 0) {
    char c = Serial1.read();
    // Send to GPS parser
    gps.encode(c);
  }

  // Print location every 200ms (5Hz)
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    lastPrint = millis();

    if (gps.location.isValid()) {
      Serial.print("Latitude: ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(", Longitude: ");
      Serial.print(gps.location.lng(), 6);
      Serial.print(", Speed (km/h): ");
      Serial.print(gps.speed.kmph());
      Serial.print(", Satellites: ");
      Serial.println(gps.satellites.value());
    } else {
      Serial.println("Waiting for valid GPS signal...");
    }
  }
}
