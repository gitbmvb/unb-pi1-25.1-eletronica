#include "config.h"
#include "bluetooth.h"
BluetoothSerial BT;

void initBT(){
  BT.begin(BT_NAME);
}

void sendBT(const String &msg){
  if (BT.hasClient()) BT.println(msg);
}
