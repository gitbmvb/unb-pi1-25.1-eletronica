#include "bmp280.h"
#include "config.h"
#include <Adafruit_BMP280.h>
#include <Wire.h>

TwoWire WireBMP = TwoWire(0);
static Adafruit_BMP280 bmp;

bool initBMP(){
  WireBMP.begin(BMP_SDA, BMP_SCL);
  return bmp.begin(0x76, &WireBMP);
}

bool readBMP(float &t, float &p){
  if (!bmp.takeForcedMeasurement()) return false;
  t = bmp.readTemperature();
  p = bmp.readPressure() / 100.0F;
  return true;
}
