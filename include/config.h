#ifndef CONFIG_H
#define CONFIG_H

// GPIO Pins
#define UART_TX GPIO_NUM_1
#define UART_RX GPIO_NUM_3
#define LED GPIO_NUM_2
#define CAN_TX GPIO_NUM_18
#define CAN_RX GPIO_NUM_5

// CAN Configuration
#define CAN_SPEED CAN_SPEED_100KBPS
#define CAN_QUEUE_LENGTH 10

// BLE Configuration
#define BLE_DEVICE_NAME "BMW 1M Buttons"
#define BLE_MANUFACTURER "BMW"
#define BLE_DELAY 500

#endif  // CONFIG_H
