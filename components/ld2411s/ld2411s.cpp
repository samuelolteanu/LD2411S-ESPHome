#include "ld2411s.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ld2411s {

static const char *const TAG = "ld2411s";

void LD2411SComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up LD2411S...");
}

void LD2411SComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "LD2411S:");
  LOG_SENSOR("  ", "Distance", this->distance_sensor_);
  LOG_SENSOR("  ", "Max Motion Distance", this->max_motion_sensor_);
  LOG_SENSOR("  ", "Min Motion Distance", this->min_motion_sensor_);
  LOG_SENSOR("  ", "Max Presence Distance", this->max_presence_sensor_);
  LOG_SENSOR("  ", "Min Presence Distance", this->min_presence_sensor_);
  LOG_SENSOR("  ", "Unoccupied Time", this->unocc_time_sensor_);
  LOG_BINARY_SENSOR("  ", "Presence", this->presence_binary_sensor_);
  LOG_BINARY_SENSOR("  ", "Motion", this->motion_binary_sensor_);
}

void LD2411SComponent::loop() {
  while (this->available()) {
    uint8_t byte;
    this->read_byte(&byte);
    this->bytes_.push_back(byte);

    size_t size = this->bytes_.size();
    
    // End of Frame is 0x55 0x55 or 0x04 0x03 0x02 0x01
    if (size >= 2) {
      if ((this->bytes_[size - 2] == 0x55 && this->bytes_[size - 1] == 0x55) ||
          (size >= 4 && this->bytes_[size - 4] == 0x04 && this->bytes_[size - 3] == 0x03 &&
           this->bytes_[size - 2] == 0x02 && this->bytes_[size - 1] == 0x01)) {
        this->process_packet_();
        this->bytes_.clear();
      }
    }
  }
}

void LD2411SComponent::process_packet_() {
  size_t size = this->bytes_.size();
  
  if (size < 3) {
    return;
  }

  // No presence/motion detected
  if (this->bytes_[0] == 0xAA && this->bytes_[1] == 0xAA && this->bytes_[2] == 0x00) {
    if (this->presence_binary_sensor_ != nullptr) {
      this->presence_binary_sensor_->publish_state(false);
    }
    if (this->motion_binary_sensor_ != nullptr) {
      this->motion_binary_sensor_->publish_state(false);
    }
    return;
  }

  // Presence and motion detected
  if (this->bytes_[0] == 0xAA && this->bytes_[1] == 0xAA && this->bytes_[2] == 0x01) {
    if (size < 5) return;
    
    if (this->presence_binary_sensor_ != nullptr) {
      this->presence_binary_sensor_->publish_state(true);
    }
    if (this->motion_binary_sensor_ != nullptr) {
      this->motion_binary_sensor_->publish_state(true);
    }

    uint16_t distance_hex = (this->bytes_[4] << 8) | this->bytes_[3];
    
    if (this->distance_sensor_ != nullptr) {
      this->distance_sensor_->publish_state(distance_hex);
    }
    return;
  }

  // Presence only (no motion)
  if (this->bytes_[0] == 0xAA && this->bytes_[1] == 0xAA && this->bytes_[2] == 0x02) {
    if (size < 5) return;
    
    if (this->presence_binary_sensor_ != nullptr) {
      this->presence_binary_sensor_->publish_state(true);
    }
    if (this->motion_binary_sensor_ != nullptr) {
      this->motion_binary_sensor_->publish_state(false);
    }

    uint16_t distance_hex = (this->bytes_[4] << 8) | this->bytes_[3];
    
    if (this->distance_sensor_ != nullptr) {
      this->distance_sensor_->publish_state(distance_hex);
    }
    return;
  }

  // Configuration response
  if (size >= 20 && this->bytes_[0] == 0xFD && this->bytes_[1] == 0xFC && 
      this->bytes_[2] == 0xFB && this->bytes_[3] == 0xFA && 
      this->bytes_[6] == 0x73 && this->bytes_[7] == 0x01) {
    
    uint16_t max_m = (this->bytes_[11] << 8) | this->bytes_[10];
    uint16_t min_m = (this->bytes_[13] << 8) | this->bytes_[12];
    uint16_t max_p = (this->bytes_[15] << 8) | this->bytes_[14];
    uint16_t min_p = (this->bytes_[17] << 8) | this->bytes_[16];
    uint16_t unocc = (this->bytes_[19] << 8) | this->bytes_[18];

    if (this->max_motion_sensor_ != nullptr) {
      this->max_motion_sensor_->publish_state(max_m);
    }
    if (this->min_motion_sensor_ != nullptr) {
      this->min_motion_sensor_->publish_state(min_m);
    }
    if (this->max_presence_sensor_ != nullptr) {
      this->max_presence_sensor_->publish_state(max_p);
    }
    if (this->min_presence_sensor_ != nullptr) {
      this->min_presence_sensor_->publish_state(min_p);
    }
    if (this->unocc_time_sensor_ != nullptr) {
      this->unocc_time_sensor_->publish_state(unocc / 10.0f);
    }
    return;
  }
}

}  // namespace ld2411s
}  // namespace esphome