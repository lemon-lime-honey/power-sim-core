#pragma once

#include <cmath>
#include <stdexcept>

#include "core/analysis/FaultStrategy.hpp"
#include "core/analysis/YBusBuilder.hpp"
#include "models/BaseSystem.hpp"
#include "models/SequenceType.hpp"

namespace powersim::core::analysis {

using namespace powersim::models;

class SingleLineToGroundFault : public FaultStrategy {
 public:
  FaultReport calculate(const models::PowerSystem& system,
                        int faultBusId) const override {
    auto faultBus = system.getBus(faultBusId);
    if (!faultBus) {
      throw std::invalid_argument("Fault bus does not exist in the system.");
    }

    math::ComplexMatrix positiveYBus =
        YBusBuilder::build(system, SequenceType::Positive);
    math::ComplexMatrix zeroYBus =
        YBusBuilder::build(system, SequenceType::Zero);

    math::ComplexMatrix positiveZBus = positiveYBus.inverse();
    math::ComplexMatrix zeroZBus = zeroYBus.inverse();

    size_t faultIdx = 0;
    bool found = false;
    for (const auto& [id, busPtr] : system.getBuses()) {
      if (id == faultBusId) {
        found = true;
        break;
      }
      faultIdx++;
    }
    if (!found) throw std::logic_error("Fault bus index mapping failed.");

    std::complex<double> z1 = positiveZBus(faultIdx, faultIdx);
    std::complex<double> z2 = z1;
    std::complex<double> z0 = zeroZBus(faultIdx, faultIdx);

    std::complex<double> totalImpedance = z0 + z1 + z2;
    double magnitude = std::abs(totalImpedance);

    if (magnitude < 1e-9) {
      throw std::runtime_error("Impedance is near zero.");
    }

    double currentRatio = 3.0 / magnitude;
    double basePower = models::BaseSystem::instance().getBasePower();
    double voltage = faultBus->getNominalVoltage();
    double capacity = basePower * currentRatio;
    double current = capacity / (std::sqrt(3.0) * voltage);

    return {faultBusId, totalImpedance, current, capacity};
  }
};
}  // namespace powersim::core::analysis