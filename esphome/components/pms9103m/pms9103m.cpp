#include "pms9103m.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pms9103m {

static const char *const TAG = "pms9103m";

void PMS9103MComponent::setup() {}

void PMS9103MComponent::loop() {}

void PMS9103MComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "PMSX003:");
  LOG_UPDATE_INTERVAL(this);
  this->check_uart_settings(9600);
}

void PMS9103MComponent::update() {}

}  // namespace pms9103m
}  // namespace esphome
