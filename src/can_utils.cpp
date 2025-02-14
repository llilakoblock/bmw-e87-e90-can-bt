#include "can_utils.h"

#include <cstring>
#include <string>

#include "log_utils.h"

// TWAI Configuration
void can_setup() {
  twai_general_config_t g_config =
      TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX, CAN_RX, TWAI_MODE_NORMAL);
  twai_timing_config_t t_config =
      TWAI_TIMING_CONFIG_100KBITS();  // Match `CAN_SPEED_100KBPS`
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
    LOG_INFO("TWAI Driver installed");
  } else {
    LOG_ERROR("Failed to install TWAI Driver");
  }

  if (twai_start() == ESP_OK) {
    LOG_INFO("TWAI Driver started");
  } else {
    LOG_ERROR("Failed to start TWAI Driver");
  }
}

void can_receive(BleKeyboard &bleKeyboard) {
  twai_message_t message;
  if (twai_receive(&message, pdMS_TO_TICKS(3)) == ESP_OK) {
    if (message.identifier == 0x1D6) {
      uint8_t command = message.data[0];
      uint8_t subcommand = message.data[1];

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
