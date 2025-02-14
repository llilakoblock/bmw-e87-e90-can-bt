#ifndef CAN_UTILS_H
#define CAN_UTILS_H

#include <BleKeyboard.h>

#include "config.h"
#include "driver/twai.h"  // TWAI (CAN) Driver

// CAN Functions
void can_setup();
void can_receive(BleKeyboard &bleKeyboard);

#endif  // CAN_UTILS_H
