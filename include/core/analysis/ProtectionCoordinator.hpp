#pragma once

#include <stdexcept>
#include <string>
#include <utility>

#include "core/analysis/TripCurve.hpp"
#include "models/PowerSystem.hpp"

namespace powersim::core::analysis {

struct TripEvent {
  std::string relayName;
  std::string cbName;
  bool tripped;
  double tripTime;
};

class ProtectionCoordinator {
 public:
  static TripEvent simulate(models::PowerSystem& system,
                            const std::string& relayName, double faultCurrent,
                            const TripCurve& curve) {
    auto relay = system.getRelay(relayName);
    if (!relay) throw std::invalid_argument("Relay not found: " + relayName);

    auto [ctName, cbName] = system.getProtectionLink(relayName);
    auto ct = system.getCT(ctName);
    auto cb = system.getCircuitBreaker(cbName);

    if (!ct || !cb)
      throw std::runtime_error("Linked CT or CB object is missing.");

    double primaryCurrent = faultCurrent * 1000.0;
    double secondaryCurrent = primaryCurrent / ct->getRatio();

    double psm = secondaryCurrent / relay->getTapSetting();
    double tripTime = curve.calculateTime(psm, relay->getTimeLever());

    if (tripTime < 0.0) {
      return {relayName, cbName, false, 0.0};
    }

    cb->open();
    return {relayName, cbName, true, tripTime};
  }
};

}  // namespace powersim::core::analysis