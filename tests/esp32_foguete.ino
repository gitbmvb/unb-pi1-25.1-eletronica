#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#define SEA_LEVEL 1013.25
#define DEFAULT_DELAY 1000
#define BMP_I2C_ADDRESS 0x76
Adafruit_BMP280 bmp;
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

float temperature, pressure, altitude;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(100);
  Serial.println(F("BMP280 Sensor event test"));

  unsigned status;
  status = bmp.begin(BMP_I2C_ADDRESS);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  bmp_temp->printSensorDetails();
}

void read_bmp_sensor() {
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  temperature = temp_event.temperature;
  pressure = pressure_event.pressure;
  altitude = bmp.readAltitude(SEA_LEVEL);
}

void print_info() {
  Serial.print(F("Temperatura = "));
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print(F("Pressão atmosférica = "));
  Serial.print(pressure);
  Serial.println(" hPa");
  Serial.print("Altitude aproximada = ");
  Serial.print(altitude);
  Serial.println(" m");
  Serial.println();
}


void loop() {
  read_bmp_sensor();
  print_info();
  delay(DEFAULT_DELAY);
}
