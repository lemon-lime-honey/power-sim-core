#pragma once
#include "InstrumentTransformer.hpp"

namespace powersim::models {
class PT : public InstrumentTransformer {
 public:
  PT(std::string name, double primaryVoltage, double secondaryVoltage = 110.0)
      : InstrumentTransformer(std::move(name), primaryVoltage,
                              secondaryVoltage) {}
};
}  // namespace powersim::models