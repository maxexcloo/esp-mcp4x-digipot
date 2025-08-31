#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/spi/spi.h"
#include "esphome/components/number/number.h"

namespace esphome {
namespace mcp414x {

// Memory addresses for MCP414X commands
static const uint8_t MCP414X_WIPER0_ADDRESS = 0x00;
static const uint8_t MCP414X_WIPER1_ADDRESS = 0x01;  // For dual potentiometers
static const uint8_t MCP414X_EEPROM0_ADDRESS = 0x02;
static const uint8_t MCP414X_EEPROM1_ADDRESS = 0x03;  // For dual potentiometers

// Command bits for MCP414X SPI interface
static const uint8_t MCP414X_WRITE_COMMAND = 0x00;  // C1=0, C0=0
static const uint8_t MCP414X_READ_COMMAND = 0x0C;   // C1=1, C0=1
static const uint8_t MCP414X_INCREMENT_COMMAND = 0x04;  // C1=0, C0=1
static const uint8_t MCP414X_DECREMENT_COMMAND = 0x08;  // C1=1, C0=0

// Maximum wiper value (7-bit: 0-128, 129 steps)
static const uint8_t MCP414X_MAX_VALUE = 128;

class MCP414X : public number::Number, public Component, public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_10MHZ> {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  void set_initial_value(uint8_t value) { this->initial_value_ = value; }

 protected:
  void control(float value) override;

  bool write_wiper_value(uint8_t value);
  bool read_wiper_value(uint8_t &value);
  bool increment_wiper();
  bool decrement_wiper();

  uint8_t create_command_byte(uint8_t address, uint8_t command, uint8_t data_bits = 0);

  uint8_t initial_value_{64};
  uint8_t current_value_{64};
};

}  // namespace mcp414x
}  // namespace esphome
