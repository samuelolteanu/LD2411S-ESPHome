#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include <vector>

namespace esphome {
namespace ld2411s {

class LD2411SComponent : public Component, public uart::UARTDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void set_distance_sensor(sensor::Sensor *sensor) { distance_sensor_ = sensor; }
  void set_max_motion_sensor(sensor::Sensor *sensor) { max_motion_sensor_ = sensor; }
  void set_min_motion_sensor(sensor::Sensor *sensor) { min_motion_sensor_ = sensor; }
  void set_max_presence_sensor(sensor::Sensor *sensor) { max_presence_sensor_ = sensor; }
  void set_min_presence_sensor(sensor::Sensor *sensor) { min_presence_sensor_ = sensor; }
  void set_unocc_time_sensor(sensor::Sensor *sensor) { unocc_time_sensor_ = sensor; }
  void set_presence_binary_sensor(binary_sensor::BinarySensor *sensor) { presence_binary_sensor_ = sensor; }
  void set_motion_binary_sensor(binary_sensor::BinarySensor *sensor) { motion_binary_sensor_ = sensor; }

 protected:
  sensor::Sensor *distance_sensor_{nullptr};
  sensor::Sensor *max_motion_sensor_{nullptr};
  sensor::Sensor *min_motion_sensor_{nullptr};
  sensor::Sensor *max_presence_sensor_{nullptr};
  sensor::Sensor *min_presence_sensor_{nullptr};
  sensor::Sensor *unocc_time_sensor_{nullptr};
  binary_sensor::BinarySensor *presence_binary_sensor_{nullptr};
  binary_sensor::BinarySensor *motion_binary_sensor_{nullptr};

  std::vector<uint8_t> bytes_;
  
  void process_packet_();
};

}  // namespace ld2411s
}  // namespace esphome