#pragma once
#include <string>

namespace powersim::models {

class LightningArrester {
 public:
  LightningArrester(std::string name, double ratedVoltage,
                    double nominalDischargeCurrent, double residualVoltage)
      : name_(std::move(name)),
        ratedVoltage_(ratedVoltage),
        nominalDischargeCurrent_(nominalDischargeCurrent),
        residualVoltage_(residualVoltage) {}

  std::string getName() const { return name_; }
  double getRatedVoltage() const { return ratedVoltage_; }
  double getNominalDischargeCurrent() const { return nominalDischargeCurrent_; }
  double getResidualVoltage() const { return residualVoltage_; }

 private:
  std::string name_;
  double ratedVoltage_;
  double nominalDischargeCurrent_;
  double residualVoltage_;
};

}  // namespace powersim::models