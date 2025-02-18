#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace pms9103m {

class PMS9103MComponent : public PollingComponent, public uart::UARTDevice {
 public:
  PMS9103MComponent() = default;
  void setup() override;
  void dump_config() override;
};

}  // namespace pms9103m
}  // namespace esphome
