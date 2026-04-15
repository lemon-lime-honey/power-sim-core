#pragma once
#include <string>

#include "CT.hpp"
#include "PT.hpp"

namespace powersim::models {

class MOF {
 public:
  MOF(std::string name, double ptPrimaryVoltage, double ctPrimaryCurrent,
      double ptSecondaryVoltage = 110.0, double ctSecondaryCurrent = 5.0)
      : name_(std::move(name)),
        pt_(name_ + "_PT", ptPrimaryVoltage, ptSecondaryVoltage),
        ct_(name_ + "_CT", ctPrimaryCurrent, ctSecondaryCurrent) {}

  std::string getName() const { return name_; }

  const PT& getPT() const { return pt_; }
  const CT& getCT() const { return ct_; }

 private:
  std::string name_;
  PT pt_;
  CT ct_;
};

}  // namespace powersim::models