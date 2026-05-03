#pragma once

#include <complex>

#include "models/PowerSystem.hpp"

namespace powersim::core::analysis {
struct FaultReport {
  int faultBusId;
  std::complex<double> theveninImpedance;
  double faultCurrent;
  double faultCapacity;
};

class FaultStrategy {
 public:
  virtual ~FaultStrategy() = default;

  virtual FaultReport calculate(const models::PowerSystem& system,
                                int faultBusId) const = 0;
};
}  // namespace powersim::core::analysis