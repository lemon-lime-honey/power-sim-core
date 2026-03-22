#pragma once
#include <string>

namespace powersim::models {
class Bus {
 public:
  Bus(int id, std::string name, double nominalVoltage)
      : id_(id), name_(std::move(name)), nominalVoltage_(nominalVoltage) {}

  int getId() const { return id_; }
  std::string getName() const { return name_; }
  double getNominalVoltage() const { return nominalVoltage_; }

 private:
  int id_;
  std::string name_;
  double nominalVoltage_;
};
}  // namespace powersim::models