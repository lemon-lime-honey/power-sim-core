#pragma once
#include <complex>
#include <numbers>
#include <string>
#include <utility>

#include "BaseSystem.hpp"

namespace powersim::models {

class Line {
 public:
  Line(std::string name, int fromBus, int toBus, double nominalVoltage,
       double resistance, double inductance, double conductance,
       double capacitance)
      : name_(std::move(name)),
        fromBus_(fromBus),
        toBus_(toBus),
        nominalVoltage_(nominalVoltage),
        resistance_(resistance),
        inductance_(inductance),
        conductance_(conductance),
        capacitance_(capacitance) {}

  std::complex<double> getImpedance() const {
    double f = BaseSystem::instance().getFrequency();
    double omega = 2.0 * std::numbers::pi * f;
    double z_base = BaseSystem::instance().getBaseImpedance(nominalVoltage_);

    if (z_base <= 0.0) return {0.0, 0.0};

    std::complex<double> z_ohm = {resistance_, omega * inductance_};
    return z_ohm / z_base;
  }

  std::complex<double> getAdmittance() const {
    double f = BaseSystem::instance().getFrequency();
    double omega = 2.0 * std::numbers::pi * f;
    double z_base = BaseSystem::instance().getBaseImpedance(nominalVoltage_);

    if (z_base <= 0.0) return {0.0, 0.0};

    std::complex<double> y_siemens = {conductance_, omega * capacitance_};
    return y_siemens * z_base;
  }

  std::pair<int, int> getConnectedBuses() const { return {fromBus_, toBus_}; }
  std::string getName() const { return name_; }

 private:
  std::string name_;
  int fromBus_, toBus_;

  double nominalVoltage_;
  double resistance_;
  double inductance_;
  double conductance_;
  double capacitance_;
};
}  // namespace powersim::models