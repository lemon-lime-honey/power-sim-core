#pragma once

namespace powersim::models {
class BaseSystem {
 public:
  static BaseSystem& instance() {
    static BaseSystem instance_;
    return instance_;
  }

  void setBase(double frequency, double basePower) {
    frequency_ = frequency;
    basePower_ = basePower;
  }

  double getFrequency() const { return frequency_; }
  double getBasePower() const { return basePower_; }

  double getBaseImpedance(double nominalVoltage) const {
    return getBaseImpedance(nominalVoltage, basePower_);
  }

  double getBaseImpedance(double voltage, double power) const {
    if (power <= 0.0) return 0.0;
    return (10.0 * voltage * voltage) / power;
  }

 private:
  BaseSystem() : frequency_(60.0), basePower_(100.0) {}

  double frequency_;
  double basePower_;
};
}  // namespace powersim::models