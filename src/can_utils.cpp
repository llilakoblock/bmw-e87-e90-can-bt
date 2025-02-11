#include "can_utils.h"

#include <cstring>
#include <string>

#include "log_utils.h"

void can_setup(CAN_device_t &CAN_cfg) {
  CAN_cfg.speed = CAN_SPEED;
  CAN_cfg.tx_pin_id = CAN_TX;
  CAN_cfg.rx_pin_id = CAN_RX;
  CAN_cfg.rx_queue = xQueueCreate(CAN_QUEUE_LENGTH, sizeof(CAN_frame_t));

  if (ESP32Can.CANInit() == 0) {
    LOG_DEBUG("CAN initialized successfully");
  } else {
    LOG_ERROR("Failed to initialize CAN");
  }
}

void can_receive(CAN_device_t &CAN_cfg, BleKeyboard &bleKeyboard) {
  CAN_frame_t frame;

  if (xQueueReceive(CAN_cfg.rx_queue, &frame, 3 * portTICK_PERIOD_MS) ==
      pdTRUE) {
    if (frame.MsgID == 0x1D6) {
      uint8_t command = frame.data.u8[0];
      uint8_t subcommand = frame.data.u8[1];

      switch (command) {
        case 0xC0:
          if (subcommand == 0x0C) {
            LOG_DEBUG("Ping");
            bleKeyboard.release(uint8_t(0));
          } else if (subcommand == 0x1C) {
            LOG_DEBUG("Rotate");
          } else if (subcommand == 0x4C) {
            LOG_DEBUG("Disk");
          }
          break;
        case 0xC8:
          LOG_DEBUG("Volume Up");
          break;
        case 0xC4:
          LOG_DEBUG("Volume Down");
          break;
        case 0xE0:
          LOG_DEBUG("Next Track");
          bleKeyboard.press(KEY_MEDIA_NEXT_TRACK);
          break;
        case 0xD0:
          LOG_DEBUG("Previous Track");
          bleKeyboard.press(KEY_MEDIA_PREVIOUS_TRACK);
          break;
        case 0xC1:
          LOG_DEBUG("Play/Pause");
          bleKeyboard.press(KEY_MEDIA_PLAY_PAUSE);
          break;
        default:
          LOG_DEBUG("Unhandled Command");
          break;
      }
    }
  }
}
