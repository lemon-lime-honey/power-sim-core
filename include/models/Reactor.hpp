#pragma once

#include <complex>
#include <string>
#include <utility>

#include "BaseSystem.hpp"

namespace powersim::models {
class Reactor {
 public:
  Reactor(std::string name, int fromBus, int toBus, double nominalVoltage,
          double ratedCapacity)
      : name_(std::move(name)),
        fromBus_(fromBus),
        toBus_(toBus),
        nominalVoltage_(nominalVoltage),
        ratedCapacity_(ratedCapacity) {}

  Reactor(std::string name, int bus, double nominalVoltage,
          double ratedCapacity)
      : Reactor(std::move(name), bus, 0, nominalVoltage, ratedCapacity) {}

  std::complex<double> getImpedance() const {
    if (ratedCapacity_ <= 0.0) return {0.0, 0.0};

    double magnitude = BaseSystem::instance().getBaseImpedance(nominalVoltage_,
                                                               ratedCapacity_);
    return {0.0, magnitude};
  }

  std::pair<int, int> getConnectedBuses() const { return {fromBus_, toBus_}; }
  std::string getName() const { return name_; }
  double getNominalVoltage() const { return nominalVoltage_; }
  double getRatedCapacity() const { return ratedCapacity_; }

 private:
  std::string name_;
  int fromBus_;
  int toBus_;
  double nominalVoltage_;
  double ratedCapacity_;
};
}  // namespace powersim::models