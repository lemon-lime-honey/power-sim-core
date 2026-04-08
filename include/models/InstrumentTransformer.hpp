#pragma once
#include <string>

namespace powersim::models {
class InstrumentTransformer {
 public:
  InstrumentTransformer(std::string name, double primaryValue, double secondaryValue)
      : name_(std::move(name)), 
        primaryValue_(primaryValue), 
        secondaryValue_(secondaryValue) {}
        
  virtual ~InstrumentTransformer() = default;

  double getRatio() const { return primaryValue_ / secondaryValue_; }
  
  double getSecondaryValue(double measuredPrimary) const {
    return measuredPrimary / getRatio();
  }

  std::string getName() const { return name_; }
  double getPrimaryValue() const { return primaryValue_; }
  double getSecondaryValueRated() const { return secondaryValue_; }

 protected:
  std::string name_;
  double primaryValue_;
  double secondaryValue_;
};
}  // namespace powersim::models