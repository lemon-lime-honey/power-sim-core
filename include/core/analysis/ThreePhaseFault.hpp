#pragma once

#include <cmath>
#include <stdexcept>

#include "core/analysis/FaultStrategy.hpp"
#include "core/analysis/YBusBuilder.hpp"
#include "models/BaseSystem.hpp"

namespace powersim::core::analysis {
class ThreePhaseFault : public FaultStrategy {
 public:
  FaultReport calculate(const models::PowerSystem& system,
                        int faultBusId) const override {
    auto faultBus = system.getBus(faultBusId);
    if (!faultBus) {
      throw std::invalid_argument("Fault bus does not exist in the system.");
    }

    math::ComplexMatrix ybus = YBusBuilder::build(system);
    math::ComplexMatrix zbus = ybus.inverse();

    size_t faultIdx = _getBusIndex(system, faultBusId);

    std::complex<double> theveninZ = zbus(faultIdx, faultIdx);
    double magnitude = std::abs(theveninZ);

    if (magnitude < 1e-9) {
      throw std::runtime_error("Thevenin impedance is near zero.");
    }

    double basePower = models::BaseSystem::instance().getBasePower();
    double voltage = faultBus->getNominalVoltage();

    double capacity = basePower / magnitude;
    double current = capacity / (std::sqrt(3.0) * voltage);

    return {faultBusId, theveninZ, current, capacity};
  }

 private:
  size_t _getBusIndex(const models::PowerSystem& system, int faultBusId) const {
    size_t idx = 0;
    for (const auto& [id, busPtr] : system.getBuses()) {
      if (id == faultBusId) return idx;
      idx++;
    }
    throw std::logic_error("Fault bus index mapping failed.");
  }
};
}  // namespace powersim::core::analysis