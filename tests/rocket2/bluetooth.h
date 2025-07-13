#pragma once
#include <BluetoothSerial.h>
extern BluetoothSerial BT;
void initBT();
void sendBT(const String &msg);
