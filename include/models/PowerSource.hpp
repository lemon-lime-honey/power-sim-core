#pragma once
#include <complex>
#include <string>

#include "models/BaseSystem.hpp"
#include "models/SequenceType.hpp"

namespace powersim::models {
class PowerSource {
 public:
  PowerSource(std::string name, double nominalVoltage,
              double positiveShortCircuitCapacity,
              double negativeShortCircuitCapacity,
              double zeroShortCircuitCapacity)
      : name_(std::move(name)),
        nominalVoltage_(nominalVoltage),
        positiveShortCircuitCapacity_(positiveShortCircuitCapacity),
        negativeShortCircuitCapacity_(negativeShortCircuitCapacity),
        zeroShortCircuitCapacity_(zeroShortCircuitCapacity) {}

  std::string getName() const { return name_; }

  std::complex<double> getImpedance(
      SequenceType type = SequenceType::Positive) const {
    double targetCapacity = positiveShortCircuitCapacity_;
    if (type == SequenceType::Negative)
      targetCapacity = negativeShortCircuitCapacity_;
    if (type == SequenceType::Zero) targetCapacity = zeroShortCircuitCapacity_;

    if (targetCapacity <= 0.0) return {0.0, 0.0};

    double basePower = BaseSystem::instance().getBasePower();
    return {0.0, basePower / targetCapacity};
  }

  std::complex<double> getAdmittance(
      SequenceType type = SequenceType::Positive) const {
    std::complex<double> impedance = getImpedance(type);
    if (std::abs(impedance) < 1e-12) return {0.0, 0.0};
    return 1.0 / impedance;
  }

 private:
  std::string name_;
  double nominalVoltage_;
  double positiveShortCircuitCapacity_;
  double negativeShortCircuitCapacity_;
  double zeroShortCircuitCapacity_;
};
}  // namespace powersim::models