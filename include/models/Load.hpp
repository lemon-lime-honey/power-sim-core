#pragma once
#include <cmath>
#include <complex>
#include <string>

namespace powersim::models {

enum class LoadType { General, Motor };

class Load {
 public:
  Load(std::string name, double activePower, double reactivePower,
       LoadType type = LoadType::General)
      : name_(std::move(name)),
        activePower_(activePower),
        reactivePower_(reactivePower),
        type_(type) {}

  double getActivePower() const { return activePower_; }
  double getReactivePower() const { return reactivePower_; }

  std::complex<double> getComplexPower() const {
    return {activePower_, reactivePower_};
  }

  double getApparentPower() const {
    return std::sqrt(activePower_ * activePower_ +
                     reactivePower_ * reactivePower_);
  }

  double getPowerFactor() const {
    double s = getApparentPower();
    return (s == 0.0) ? 1.0 : (activePower_ / s);
  }

  LoadType getType() const { return type_; }

  std::string getName() const { return name_; }

 private:
  std::string name_;
  double activePower_;
  double reactivePower_;
  LoadType type_;
};
}  // namespace powersim::models