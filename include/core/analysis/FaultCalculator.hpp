#pragma once

#include <stdexcept>
#include <string>

#include "core/analysis/FaultStrategy.hpp"
#include "models/PowerSystem.hpp"

namespace powersim::core::analysis {

class FaultCalculator {
 public:
  static FaultReport calculate(const models::PowerSystem& system,
                               int faultBusId, const FaultStrategy& strategy) {
    return strategy.calculate(system, faultBusId);
  }

  static bool evaluateBreakerSafety(const models::PowerSystem& system,
                                    const std::string& cbName,
                                    double faultCapacity) {
    auto cb = system.getCircuitBreaker(cbName);
    if (!cb) {
      throw std::invalid_argument("Circuit breaker not found: " + cbName);
    }
    return cb->getBreakingCapacity() >= faultCapacity;
  }
};
}  // namespace powersim::core::analysis