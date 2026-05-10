#pragma once

#include <cmath>

namespace powersim::core::analysis {
class TripCurve {
 public:
  virtual ~TripCurve() = default;
  virtual double calculateTime(double psm, double timeLever) const = 0;
};

class StandardInverseCurve : public TripCurve {
 public:
  double calculateTime(double psm, double timeLever) const override {
    if (psm <= 1.0) return -1.0;
    return timeLever * (0.14 / (std::pow(psm, 0.02) - 1.0));
  }
};
}  // namespace powersim::core::analysis