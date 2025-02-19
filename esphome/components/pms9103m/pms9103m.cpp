#include "pms9103m.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace pms9103m {

static const char *const TAG = "pms9103m";
static const uint8_t PMS9103M_WAKE_UP_CMD[] = {0x42, 0x4d, 0xe4, 0x00, 0x01, 0x01, 0x74};
static const uint8_t PMS9103M_SET_ACTIVE_CMD[] = {0x42, 0x4d, 0xe1, 0x00, 0x01, 0x01, 0x71};

void PMS9103MComponent::setup() {
  ESP_LOGV(TAG, "sending wake up command");
  this->write_array(PMS9103M_WAKE_UP_CMD, sizeof(PMS9103M_WAKE_UP_CMD));

  ESP_LOGV(TAG, "sending set active command");
  this->write_array(PMS9103M_SET_ACTIVE_CMD, sizeof(PMS9103M_SET_ACTIVE_CMD));
}

void PMS9103MComponent::loop() {}

void PMS9103MComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "PMS9103M:");
  LOG_UPDATE_INTERVAL(this);
  this->check_uart_settings(9600);
}

void PMS9103MComponent::update() {
  const uint8_t num_bytes = 32;
  uint8_t buffer_u8[num_bytes];

  while (this->available() >= num_bytes) {
    this->read_array(buffer_u8, num_bytes);
  }

  // check prefix
  if (buffer_u8[0] != 0x42 || buffer_u8[1] != 0x4d) {
    return;
  }

  uint16_t sum = 0;
  for (uint8_t i = 0; i < num_bytes - 2; i++)
    sum += buffer_u8[i];

  uint16_t buffer_u16[13];
  for (uint8_t i = 0; i < 13; i++) {
    buffer_u16[i] = buffer_u8[2 + i * 2 + 1];
    buffer_u16[i] += (buffer_u8[2 + i * 2] << 8);
  }

  uint8_t version = buffer_u8[2 + 26];
  uint8_t checksum = buffer_u8[2 + 27];

  if (sum != checksum) {
    ESP_LOGD(TAG, "Invalid sum from data: %s", format_hex_pretty(buffer_u8, num_bytes).c_str());

    return;
  }

  ESP_LOGD(TAG, "Data from sensor: %s", format_hex_pretty(buffer_u16, num_bytes).c_str());
}

}  // namespace pms9103m
}  // namespace esphome
