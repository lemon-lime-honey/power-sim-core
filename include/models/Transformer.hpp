#pragma once
#include <complex>
#include <string>
#include <utility>

#include "BaseSystem.hpp"

namespace powersim::models {

class Transformer {
 public:
  Transformer(std::string name, int primaryBus, int secondaryBus,
              double ratedPower, double primaryVoltage, double secondaryVoltage,
              std::complex<double> percentImpedance)
      : name_(std::move(name)),
        primaryBus_(primaryBus),
        secondaryBus_(secondaryBus),
        ratedPower_(ratedPower),
        primaryVoltage_(primaryVoltage),
        secondaryVoltage_(secondaryVoltage),
        percentImpedance_(percentImpedance) {}

  std::complex<double> getImpedance() const {
    if (ratedPower_ <= 0.0) return {0.0, 0.0};
    double sysBase = BaseSystem::instance().getBasePower();
    return (percentImpedance_ / 100.0) * (sysBase / ratedPower_);
  }

  std::pair<int, int> getConnectedBuses() const {
    return {primaryBus_, secondaryBus_};
  }
  std::string getName() const { return name_; }
  double getRatedPower() const { return ratedPower_; }
  double getPrimaryVoltage() const { return primaryVoltage_; }
  double getSecondaryVoltage() const { return secondaryVoltage_; }

 private:
  std::string name_;
  int primaryBus_, secondaryBus_;
  double ratedPower_;
  double primaryVoltage_, secondaryVoltage_;
  std::complex<double> percentImpedance_;
};
}  // namespace powersim::models