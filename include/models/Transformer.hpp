#pragma once
#include <complex>
#include <string>
#include <utility>

#include "models/BaseSystem.hpp"
#include "models/SequenceType.hpp"
#include "models/WindingConnection.hpp"

namespace powersim::models {
class Transformer {
 public:
  Transformer(
      std::string name, int primaryBus, int secondaryBus, double ratedPower,
      double primaryVoltage, double secondaryVoltage,
      std::complex<double> positiveImpedance,
      std::complex<double> zeroImpedance,
      WindingConnection primaryConnection = WindingConnection::WyeGrounded,
      WindingConnection secondaryConnection = WindingConnection::WyeGrounded)
      : name_(std::move(name)),
        primaryBus_(primaryBus),
        secondaryBus_(secondaryBus),
        ratedPower_(ratedPower),
        primaryVoltage_(primaryVoltage),
        secondaryVoltage_(secondaryVoltage),
        positiveImpedance_(positiveImpedance),
        zeroImpedance_(zeroImpedance),
        primaryConnection_(primaryConnection),
        secondaryConnection_(secondaryConnection) {}

  std::string getName() const { return name_; }
  std::pair<int, int> getConnectedBuses() const {
    return {primaryBus_, secondaryBus_};
  }

  WindingConnection getPrimaryConnection() const { return primaryConnection_; }
  WindingConnection getSecondaryConnection() const {
    return secondaryConnection_;
  }

  std::complex<double> getImpedance(
      SequenceType type = SequenceType::Positive) const {
    if (ratedPower_ <= 0.0) return {0.0, 0.0};

    std::complex<double> targetImpedance =
        (type == SequenceType::Zero) ? zeroImpedance_ : positiveImpedance_;
    double basePower = BaseSystem::instance().getBasePower();

    return targetImpedance * (basePower / ratedPower_);
  }

  std::complex<double> getAdmittance(
      SequenceType type = SequenceType::Positive) const {
    std::complex<double> impedance = getImpedance(type);
    if (std::abs(impedance) < 1e-12) return {0.0, 0.0};
    return 1.0 / impedance;
  }

 private:
  std::string name_;
  int primaryBus_, secondaryBus_;
  double ratedPower_, primaryVoltage_, secondaryVoltage_;
  std::complex<double> positiveImpedance_;
  std::complex<double> zeroImpedance_;
  WindingConnection primaryConnection_;
  WindingConnection secondaryConnection_;
};
}  // namespace powersim::models