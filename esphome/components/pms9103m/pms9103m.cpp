#include "pms9103m.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pms9103m {

static const char *const TAG = "pms9103m";

void PMS9103MComponent::setup() {}

void PMS9103MComponent::loop() {}

void PMS9103MComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "PMS9103M:");
  LOG_UPDATE_INTERVAL(this);
  this->check_uart_settings(9600);
}

void PMS9103MComponent::update() {
  const uint8_t num_bytes = 32;
  uint8_t buffer[num_bytes];

  while (this->available() >= 32) {
    this->read_byte(&buffer[this->data_index_]);
  }

  for (uint8_t i = 0; i < num_bytes; i++)
    ESP_LOGD(TAG, "%02X", buffer[i]);
}

}  // namespace pms9103m
}  // namespace esphome
