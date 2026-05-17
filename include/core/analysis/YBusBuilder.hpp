#pragma once

#include <map>
#include <memory>
#include <vector>

#include "core/math/ComplexMatrix.hpp"
#include "models/PowerSystem.hpp"
#include "models/SequenceType.hpp"
#include "models/WindingConnection.hpp"

namespace powersim::core::analysis {

class YBusBuilder {
 public:
  static math::ComplexMatrix build(
      const models::PowerSystem& system,
      models::SequenceType type = models::SequenceType::Positive) {
    const auto& buses = system.getBuses();
    size_t n = buses.size();

    std::map<int, size_t> busIdxMap;
    size_t idx = 0;
    for (const auto& [busId, busPtr] : buses) {
      busIdxMap[busId] = idx++;
    }

    math::ComplexMatrix ybus(n, n);

    for (const auto& [name, line] : system.getLines()) {
      auto [from, to] = line->getConnectedBuses();
      size_t i = busIdxMap[from];
      size_t j = busIdxMap[to];

      std::complex<double> seriesY = 1.0 / line->getImpedance(type);
      std::complex<double> shuntY = line->getAdmittance(type);

      ybus(i, i) += seriesY + (shuntY / 2.0);
      ybus(j, j) += seriesY + (shuntY / 2.0);
      ybus(i, j) -= seriesY;
      ybus(j, i) -= seriesY;
    }

    for (const auto& [name, tx] : system.getTransformers()) {
      auto [p, s] = tx->getConnectedBuses();
      size_t i = busIdxMap[p];
      size_t j = busIdxMap[s];

      std::complex<double> seriesY = 1.0 / tx->getImpedance(type);

      if (type == models::SequenceType::Zero) {
        auto pConn = tx->getPrimaryConnection();
        auto sConn = tx->getSecondaryConnection();
        bool pGrounded = (pConn == models::WindingConnection::WyeGrounded);
        bool sGrounded = (sConn == models::WindingConnection::WyeGrounded);
        bool pDelta = (pConn == models::WindingConnection::Delta);
        bool sDelta = (sConn == models::WindingConnection::Delta);

        if (pGrounded && sGrounded) {
          ybus(i, i) += seriesY;
          ybus(j, j) += seriesY;
          ybus(i, j) -= seriesY;
          ybus(j, i) -= seriesY;
        } else if (pGrounded && sDelta) {
          ybus(i, i) += seriesY;
        } else if (pDelta && sGrounded) {
          ybus(j, j) += seriesY;
        }
      } else {
        ybus(i, i) += seriesY;
        ybus(j, j) += seriesY;
        ybus(i, j) -= seriesY;
        ybus(j, i) -= seriesY;
      }
    }

    for (const auto& [name, sourcePair] : system.getPowerSources()) {
      auto source = sourcePair.first;
      int busId = sourcePair.second;
      size_t i = busIdxMap[busId];

      std::complex<double> y = 1.0 / source->getImpedance(type);
      ybus(i, i) += y;
    }

    return ybus;
  }
};
}  // namespace powersim::core::analysis