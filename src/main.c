// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.
#include <BleKeyboard.h>
#include <CAN_config.h>
#include <ESP32CAN.h>
#include <hal/log.h>
#include <string.h>

#define UART_TX 1
#define UART_RX 3
#define LED 2

CAN_device_t CAN_cfg;
BleKeyboard bleKeyboard("BMW 1M Buttons", "BMW", 100);
MediaKeyReport last_report{};
CAN_frame_t frame;

void print_can_frame_raw(const CAN_frame_t &frame) {
  char str[100];
  memset(str, 0, sizeof(str));

  unsigned char *pin = (unsigned char *)&frame;
  const char *hex = "0123456789ABCDEF";
  char *pout = str;
  int i = 0;
  for (; i < sizeof(frame); ++i) {
    *pout++ = hex[(*pin >> 4) & 0xF];
    *pout++ = hex[(*pin++) & 0xF];
    *pout++ = ' ';
  }
  *pout++ = hex[(*pin >> 4) & 0xF];
  *pout++ = hex[(*pin) & 0xF];
  *pout = '\0';

  log_v(str);
}

void print_can_frame_parsed(const CAN_frame_t &frame) {
  char str[250];
  char fmt_str[50];
  memset(str, 0, sizeof(str));
  memset(fmt_str, 0, sizeof(fmt_str));

  if (frame.FIR.B.FF == CAN_frame_std) {
    strcat(str, "New standard frame:\n");
  } else {
    strcat(str, "New extended frame:\n");
  }

  if (frame.FIR.B.RTR == CAN_RTR) {
    sprintf(fmt_str, "RTR from 0x%08X, DLC %d\r\n", frame.MsgID,
            frame.FIR.B.DLC);
    strcat(str, fmt_str);
  } else {
    sprintf(fmt_str, "From 0x%08X, DLC %d, Data: ", frame.MsgID,
            frame.FIR.B.DLC);
    strcat(str, fmt_str);

    for (int i = 0; i < frame.FIR.B.DLC; i++) {
      sprintf(fmt_str, "0x%02X ", frame.data.u8[i]);
      strcat(str, fmt_str);
    }
    strcat(str, "\n");
  }

  log_v(str);
}

void filter_1d6_message(const CAN_frame_t &frame) {
  if (frame.MsgID == 0x1D6) {
    if (frame.data.u8[0] == 0xC0 && frame.data.u8[1] == 0x0C) {
      log_d("Ping");

      if (last_report[0] != 0 || last_report[1] != 0 || last_report[2] != 0) {
        log_d("Sending zero report");
        bleKeyboard.release(last_report);
        last_report = {};
      }
    }

    if (frame.data.u8[0] == 0xC8 && frame.data.u8[1] == 0x0C) {
      // last_report = KEY_MEDIA_VOLUME_UP;
      // bleKeyboard.press(KEY_MEDIA_VOLUME_UP);
      log_d("Volume Up");
    }
    if (frame.data.u8[0] == 0xC4 && frame.data.u8[1] == 0x0C) {
      // last_report = KEY_MEDIA_VOLUME_DOWN;
      // bleKeyboard.press(KEY_MEDIA_VOLUME_DOWN);
      log_d("Volume Down");
    }
    if (frame.data.u8[0] == 0xE0 && frame.data.u8[1] == 0x0C) {
      last_report = KEY_MEDIA_NEXT_TRACK;
      bleKeyboard.press(KEY_MEDIA_NEXT_TRACK);
      log_d("Up");
    }
    if (frame.data.u8[0] == 0xD0 && frame.data.u8[1] == 0x0C) {
      last_report = KEY_MEDIA_PREVIOUS_TRACK;
      bleKeyboard.press(KEY_MEDIA_PREVIOUS_TRACK);
      log_d("Down");
    }
    if (frame.data.u8[0] == 0xC1 && frame.data.u8[1] == 0x0C) {
      last_report = KEY_MEDIA_PLAY_PAUSE;
      bleKeyboard.press(KEY_MEDIA_PLAY_PAUSE);
      log_d("Telephone");
    }
    if (frame.data.u8[0] == 0xC0 && frame.data.u8[1] == 0x0D) {
      last_report = KEY_MEDIA_VOICE_COMMAND;
      bleKeyboard.press(KEY_MEDIA_VOICE_COMMAND);
      log_d("Voice Command");
    }
    if (frame.data.u8[0] == 0xC0 && frame.data.u8[1] == 0x1C) {
      log_d("Rotate");
    }
    if (frame.data.u8[0] == 0xC0 && frame.data.u8[1] == 0x4C) {
      log_d("Disk");
    }
  }
}

void led_setup() { gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT); }

void serial_setup() {
  // Serial.begin(115200);
  // Serial.begin(115200, SERIAL_8N1, 16, 17);
}

void ble_setup() {
  // Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  bleKeyboard.setDelay(500);
}

void can_setup() {
  /* set CAN pins and baudrate */
  CAN_cfg.speed = CAN_SPEED_100KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_18;
  CAN_cfg.rx_pin_id = GPIO_NUM_5;
  /* create a queue for CAN receiving */
  CAN_cfg.rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));
  // initialize CAN Module
  if (ESP32Can.CANInit() == 0) {
    bleKeyboard.printf("CAN inited");
    gpio_set_level(GPIO_NUM_2, 1);
  } else {
    bleKeyboard.printf("Failed to init CAN");
    gpio_set_level(GPIO_NUM_2, 0);
  }
}

void can_receive() {
  // Receive next CAN frame from queue
  if (xQueueReceive(CAN_cfg.rx_queue, &frame, 3 * portTICK_PERIOD_MS) ==
      pdTRUE) {
    gpio_set_level(GPIO_NUM_2, 0);

    // print_can_frame_raw(frame);
    // print_can_frame_parsed(frame);
    filter_1d6_message(frame);

    gpio_set_level(GPIO_NUM_2, 1);
  }
}

void setup() {
  led_setup();
  serial_setup();
  ble_setup();
  can_setup();
}

void loop() { can_receive(); }