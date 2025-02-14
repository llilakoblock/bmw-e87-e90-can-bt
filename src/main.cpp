#include "ble_keyboard_utils.h"
#include "can_utils.h"
#include "config.h"
#include "log_utils.h"

BleKeyboard bleKeyboard(BLE_DEVICE_NAME, BLE_MANUFACTURER, 100);

void setup() {
  // Setup LED
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);

  // Setup BLE and CAN
  ble_setup(bleKeyboard);
  // can_setup();

  LOG_INFO("Setup complete");
}

void loop() { can_receive(bleKeyboard); }