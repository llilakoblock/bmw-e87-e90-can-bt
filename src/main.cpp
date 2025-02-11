#include "ble_keyboard_utils.h"
#include "can_utils.h"
#include "config.h"
#include "log_utils.h"

BleKeyboard bleKeyboard(BLE_DEVICE_NAME, BLE_MANUFACTURER, 100);
CAN_device_t CAN_cfg;

void setup() {
  // Setup LED
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);

  // Setup BLE and CAN
  ble_setup(bleKeyboard);
  can_setup(CAN_cfg);

  LOG_INFO("Setup complete");
}

void loop() { can_receive(CAN_cfg, bleKeyboard); }
