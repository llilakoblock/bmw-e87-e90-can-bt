#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include "esp_log.h"

// Define your logging tag
#define LOG_TAG "BMW"

// Logging macros
#define LOG_INFO(format, ...) ESP_LOGI(LOG_TAG, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) ESP_LOGD(LOG_TAG, format, ##__VA_ARGS__)
#define LOG_VERBOSE(format, ...) ESP_LOGV(LOG_TAG, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) ESP_LOGE(LOG_TAG, format, ##__VA_ARGS__)

#endif  // LOG_UTILS_H
