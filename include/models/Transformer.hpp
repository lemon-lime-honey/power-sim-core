#pragma once
#include <complex>
#include <string>
#include <utility>

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

  std::complex<double> getPercentImpedance(double baseMva) const {
    if (ratedPower_ <= 0.0) return {0.0, 0.0};
    return percentImpedance_ * (baseMva / ratedPower_);
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
  int primaryBus_;
  int secondaryBus_;
  double ratedPower_;
  double primaryVoltage_;
  double secondaryVoltage_;
  std::complex<double> percentImpedance_;
};
}  // namespace powersim::models