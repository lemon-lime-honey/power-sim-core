#pragma once
#include <cmath>
#include <complex>
#include <numbers>
#include <string>

#include "BaseSystem.hpp"

namespace powersim::models {
class PowerSource {
 public:
  PowerSource(std::string name, double nominalVoltage,
              double shortCircuitCapacity = 0.0, double voltageAngle_deg = 0.0)
      : name_(std::move(name)),
        nominalVoltage_(nominalVoltage),
        shortCircuitCapacity_(shortCircuitCapacity),
        voltageAngle_(voltageAngle_deg) {}

  std::complex<double> getPhasorVoltage() const {
    double v_phase = nominalVoltage_ / std::sqrt(3.0);
    double radians = voltageAngle_ * std::numbers::pi / 180.0;
    return {v_phase * std::cos(radians), v_phase * std::sin(radians)};
  }

  std::complex<double> getImpedance() const {
    if (shortCircuitCapacity_ <= 0.0) return {0.0, 0.0};
    double pu_reactance =
        BaseSystem::instance().getBasePower() / shortCircuitCapacity_;
    return {0.0, pu_reactance};
  }

  std::string getName() const { return name_; }
  double getNominalVoltage() const { return nominalVoltage_; }
  double getShortCircuitCapacity() const { return shortCircuitCapacity_; }

 private:
  std::string name_;
  double nominalVoltage_;
  double shortCircuitCapacity_;
  double voltageAngle_;
};
}  // namespace powersim::models