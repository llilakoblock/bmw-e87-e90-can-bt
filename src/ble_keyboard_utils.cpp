#include "ble_keyboard_utils.h"

void ble_setup(BleKeyboard &bleKeyboard) {
  bleKeyboard.begin();
  bleKeyboard.setDelay(BLE_DELAY);
}
