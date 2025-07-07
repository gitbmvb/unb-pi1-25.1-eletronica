#pragma once

// I2C pins for BMP280
#define BMP_SDA 21
#define BMP_SCL 22

// I2C pins for MPU6050
#define MPU_SDA 19
#define MPU_SCL 18

// GPS UART pins & baud
#define GPS_SERIAL_NUM 2
#define GPS_RX 16
#define GPS_TX 17
#define GPS_BAUD 9600

// Bluetooth
#define BT_NAME "ESP32_Sensor"

// MQTT broker settings
static const char* MQTT_BROKER = "mqtt.eclipseprojects.io";
static const uint16_t MQTT_PORT = 1883;
static const char* MQTT_TOPIC = "esp32/sensors";

// WiFi credentials
static const char* WIFI_SSID = "YOUR_SSID";
static const char* WIFI_PASS = "YOUR_PASSWORD";
