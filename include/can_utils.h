#ifndef CAN_UTILS_H
#define CAN_UTILS_H

#include <CAN_config.h>
#include <ESP32CAN.h>

#include "config.h"
#include <BleKeyboard.h>

// CAN Functions
void can_setup(CAN_device_t &CAN_cfg);
void can_receive(CAN_device_t &CAN_cfg, BleKeyboard &bleKeyboard);

#endif  // CAN_UTILS_H
