#!/usr/bin/env bash

set -e

# 1. Ensure Arduino CLI is installed
if ! command -v arduino-cli &> /dev/null; then
  echo "arduino-cli not found! Please install it first."
  exit 1
fi

# 2. Update index
arduino-cli core update-index

# 3. Install ESP32 board (Arduino maintained)
arduino-cli core install arduino:esp32
echo "✅ ESP32 board package installed."

# 4. Install required libraries
libs=(
  "Adafruit BMP280 library@1.0.6"
  "Adafruit BMP280@^3.0.0" 
  "Adafruit MPU6050@^1.2.0"
  "TinyGPSPlus@1.0.1"
  "PubSubClient@2.8"
  # BluetoothSerial is built into ESP32 core; no need to install
)

for lib in "${libs[@]}"; do
  echo "Installing library: $lib"
  arduino-cli lib install "$lib"
done

echo "✅ All libraries installed!"
