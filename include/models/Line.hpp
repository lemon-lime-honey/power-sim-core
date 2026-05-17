#pragma once
#include <complex>
#include <numbers>
#include <string>

#include "models/BaseSystem.hpp"
#include "models/SequenceType.hpp"

namespace powersim::models {
class Line {
 public:
  Line(std::string name, int fromBus, int toBus, double nominalVoltage,
       double positiveResistance, double positiveInductance,
       double positiveShuntConductance, double positiveShuntCapacitance,
       double zeroResistance, double zeroInductance,
       double zeroShuntConductance, double zeroShuntCapacitance)
      : name_(std::move(name)),
        fromBus_(fromBus),
        toBus_(toBus),
        nominalVoltage_(nominalVoltage),
        positiveResistance_(positiveResistance),
        positiveInductance_(positiveInductance),
        positiveShuntConductance_(positiveShuntConductance),
        positiveShuntCapacitance_(positiveShuntCapacitance),
        zeroResistance_(zeroResistance),
        zeroInductance_(zeroInductance),
        zeroShuntConductance_(zeroShuntConductance),
        zeroShuntCapacitance_(zeroShuntCapacitance) {}

  std::string getName() const { return name_; }
  std::pair<int, int> getConnectedBuses() const { return {fromBus_, toBus_}; }

  std::complex<double> getImpedance(
      SequenceType type = SequenceType::Positive) const {
    double baseImpedance =
        BaseSystem::instance().getBaseImpedance(nominalVoltage_);
    if (baseImpedance <= 0.0) return {0.0, 0.0};

    double omega =
        2.0 * std::numbers::pi * BaseSystem::instance().getFrequency();
    double resistance =
        (type == SequenceType::Zero) ? zeroResistance_ : positiveResistance_;
    double inductance =
        (type == SequenceType::Zero) ? zeroInductance_ : positiveInductance_;

    return std::complex<double>{resistance, omega * inductance} / baseImpedance;
  }

  std::complex<double> getAdmittance(
      SequenceType type = SequenceType::Positive) const {
    double baseImpedance =
        BaseSystem::instance().getBaseImpedance(nominalVoltage_);
    if (baseImpedance <= 0.0) return {0.0, 0.0};

    double omega =
        2.0 * std::numbers::pi * BaseSystem::instance().getFrequency();
    double conductance = (type == SequenceType::Zero)
                             ? zeroShuntConductance_
                             : positiveShuntConductance_;
    double capacitance = (type == SequenceType::Zero)
                             ? zeroShuntCapacitance_
                             : positiveShuntCapacitance_;

    return std::complex<double>{conductance, omega * capacitance} *
           baseImpedance;
  }

 private:
  std::string name_;
  int fromBus_, toBus_;
  double nominalVoltage_;

  double positiveResistance_;
  double positiveInductance_;
  double positiveShuntConductance_;
  double positiveShuntCapacitance_;

  double zeroResistance_;
  double zeroInductance_;
  double zeroShuntConductance_;
  double zeroShuntCapacitance_;
};
}  // namespace powersim::models