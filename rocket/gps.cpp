#include "gps.h"
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "config.h"

TinyGPSPlus gps;
HardwareSerial gpsSerial(GPS_SERIAL_NUM);

bool initGPS(){
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX, GPS_TX);
  return true;
}

bool readGPS(GPSData &d){
  unsigned long start = millis();
  while (millis() - start < 2000){
    while (gpsSerial.available()) gps.encode(gpsSerial.read());
    if (gps.location.isUpdated()){
      d.lat = gps.location.lat();
      d.lng = gps.location.lng();
      d.altitude = gps.altitude.meters();
      d.speed = gps.speed.kmph();
      return true;
    }
  }
  return false;
}
