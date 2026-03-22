#pragma once
#include <complex>
#include <numbers>
#include <string>
#include <utility>

#include "BaseSystem.hpp"

namespace powersim::models {

class Line {
 public:
  Line(std::string name, int fromBus, int toBus, double resistance,
       double inductance, double conductance, double capacitance)
      : name_(std::move(name)),
        fromBus_(fromBus),
        toBus_(toBus),
        resistance_(resistance),
        inductance_(inductance),
        conductance_(conductance),
        capacitance_(capacitance) {}

  std::complex<double> getImpedance() const {
    double f = BaseSystem::instance().getFrequency();
    double omega = 2.0 * std::numbers::pi * f;
    return {resistance_, omega * inductance_};
  }

  std::complex<double> getAdmittance() const {
    double f = BaseSystem::instance().getFrequency();
    double omega = 2.0 * std::numbers::pi * f;
    return {conductance_, omega * capacitance_};
  }

  std::pair<int, int> getConnectedBuses() const { return {fromBus_, toBus_}; }
  std::string getName() const { return name_; }

 private:
  std::string name_;
  int fromBus_, toBus_;

  double resistance_;
  double inductance_;
  double conductance_;
  double capacitance_;
};
}  // namespace powersim::models