#pragma once
struct GPSData { double lat, lng; float speed, altitude; };
bool initGPS();
bool readGPS(GPSData &d);
