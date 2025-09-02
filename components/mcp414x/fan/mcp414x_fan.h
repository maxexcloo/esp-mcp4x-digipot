#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/fan/fan.h"
#include "../mcp414x.h"

namespace esphome {
namespace mcp414x {

class MCP414XFan : public fan::Fan, public Component {
 public:
  MCP414XFan(int speed_count) : speed_count_(speed_count) {}

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  void set_parent(MCP414X *parent) { this->parent_ = parent; }

  fan::FanTraits get_traits() override { return this->traits_; }

 protected:
  void control(const fan::FanCall &call) override;
  void write_state_();

  uint8_t speed_level_to_wiper_value(int speed_level);

  MCP414X *parent_{nullptr};
  int speed_count_;
  fan::FanTraits traits_;
  uint8_t current_wiper_value_{0};
};

}  // namespace mcp414x
}  // namespace esphome
