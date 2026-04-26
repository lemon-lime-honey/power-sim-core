#pragma once

namespace powersim::models {
class BaseSystem {
 public:
  static BaseSystem& instance() {
    static BaseSystem instance_;
    return instance_;
  }

  void setBase(double frequency, double basePower_MVA) {
    frequency_ = frequency;
    basePower_ = basePower_MVA;
  }

  double getFrequency() const { return frequency_; }
  double getBasePower() const { return basePower_; }

  double getBaseImpedance(double nominalVoltage_kV) const {
    if (basePower_ <= 0.0) return 0.0;
    return (nominalVoltage_kV * nominalVoltage_kV) / basePower_;
  }

 private:
  BaseSystem() : frequency_(60.0), basePower_(100.0) {}

  double frequency_;
  double basePower_;
};
}  // namespace powersim::models