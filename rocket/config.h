#pragma once
#include <cstdint>

// I2C para sensores
#define MPU_SDA 21
#define MPU_SCL 22
#define BMP_SDA 17
#define BMP_SCL 16

// GPS
#define GPS_SERIAL_NUM 2
#define GPS_RX 26
#define GPS_TX 27
#define GPS_BAUD 9600

// Bluetooth
#define BT_NAME "ESP32_BT"

// Wi-Fi
#define WIFI_SSID "SEU_SSID"
#define WIFI_PASS "SUA_SENHA"

// MQTT
static const char* MQTT_BROKER = "broker.hivemq.com";
static const uint16_t MQTT_PORT = 1883;
static const char* MQTT_TOPIC = "rocket/telemetry";
