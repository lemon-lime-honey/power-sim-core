#pragma once

#include <cmath>
#include <string>

#include "Switch.hpp"

namespace powersim::models {

class CircuitBreaker : public Switch {
 public:
  CircuitBreaker(std::string name, double ratedVoltage,
                 double ratedBreakingCurrent, bool isClosed = true)
      : Switch(std::move(name), isClosed),
        ratedVoltage_(ratedVoltage),
        ratedBreakingCurrent_(ratedBreakingCurrent) {}

  double getBreakingCapacity() const {
    return std::sqrt(3.0) * ratedVoltage_ * ratedBreakingCurrent_;
  }

  double getRatedVoltage() const { return ratedVoltage_; }
  double getRatedBreakingCurrent() const { return ratedBreakingCurrent_; }

 private:
  double ratedVoltage_;
  double ratedBreakingCurrent_;
};

}  // namespace powersim::models