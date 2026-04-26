#pragma once
#include <cmath>
#include <complex>
#include <string>

namespace powersim::models {

enum class LoadType { General, Motor };

class Load {
 public:
  Load(std::string name, int connectedBus, double activePower,
       double reactivePower, LoadType type = LoadType::General)
      : name_(std::move(name)),
        connectedBus_(connectedBus),
        activePower_(activePower),
        reactivePower_(reactivePower),
        type_(type) {}

  int getConnectedBus() const { return connectedBus_; }

  double getActivePower() const {
    return activePower_ / BaseSystem::instance().getBasePower();
  }

  double getReactivePower() const {
    return reactivePower_ / BaseSystem::instance().getBasePower();
  }

  std::complex<double> getComplexPower() const {
    return {getActivePower(), getReactivePower()};
  }

  double getApparentPower() const {
    double p = getActivePower();
    double q = getReactivePower();
    return std::sqrt(p * p + q * q);
  }

  double getPowerFactor() const {
    double s = getApparentPower();
    return (s == 0.0) ? 1.0 : (getActivePower() / s);
  }

  LoadType getType() const { return type_; }
  std::string getName() const { return name_; }

 private:
  std::string name_;
  int connectedBus_;
  double activePower_;
  double reactivePower_;
  LoadType type_;
};
}  // namespace powersim::models