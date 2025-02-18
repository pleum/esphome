#include "pms9103m.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

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

  while (this->available() >= num_bytes) {
    this->read_array(buffer, num_bytes);
  }

  ESP_LOGD(TAG, "Data from sensor: %s", format_hex_pretty(buffer, num_bytes).c_str());
}

}  // namespace pms9103m
}  // namespace esphome
