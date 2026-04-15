#pragma once
#include "InstrumentTransformer.hpp"

namespace powersim::models {
class CT : public InstrumentTransformer {
 public:
  CT(std::string name, double primaryCurrent, double secondaryCurrent = 5.0)
      : InstrumentTransformer(std::move(name), primaryCurrent,
                              secondaryCurrent) {}
};
}  // namespace powersim::models