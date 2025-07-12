#include "bluetooth.h"
#include "config.h"
BluetoothSerial BT;

void initBT(){
  BT.begin(BT_NAME);
}

void sendBT(const String &msg){
  if (BT.hasClient()) BT.println(msg);
}
