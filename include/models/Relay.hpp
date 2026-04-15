#pragma once
#include <string>

namespace powersim::models {

enum class RelayType { OCR, OVR, UVR, DGR };

class Relay {
 public:
  Relay(std::string name, RelayType type, double tapSetting,
        double timeLever = 10.0)
      : name_(std::move(name)),
        type_(type),
        tapSetting_(tapSetting),
        timeLever_(timeLever) {}

  std::string getName() const { return name_; }
  RelayType getType() const { return type_; }
  double getTapSetting() const { return tapSetting_; }
  double getTimeLever() const { return timeLever_; }

 private:
  std::string name_;
  RelayType type_;
  double tapSetting_;
  double timeLever_;
};

}  // namespace powersim::models