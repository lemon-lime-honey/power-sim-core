#pragma once

#include <map>
#include <memory>
#include <vector>

#include "core/math/ComplexMatrix.hpp"
#include "models/PowerSystem.hpp"

namespace powersim::core::analysis {
using namespace powersim::models;
using namespace powersim::core::math;

class YBusBuilder {
 public:
  static ComplexMatrix build(const PowerSystem& system) {
    const auto& buses = system.getBuses();
    size_t n = buses.size();

    std::map<int, size_t> busIdxMap;
    size_t idx = 0;
    for (const auto& [busId, busPtr] : buses) {
      busIdxMap[busId] = idx++;
    }

    ComplexMatrix ybus(n, n);

    for (const auto& [name, line] : system.getLines()) {
      auto [from, to] = line->getConnectedBuses();
      size_t i = busIdxMap[from];
      size_t j = busIdxMap[to];

      std::complex<double> y = 1.0 / line->getImpedance();

      ybus(i, i) += y;
      ybus(j, j) += y;
      ybus(i, j) -= y;
      ybus(j, i) -= y;
    }

    for (const auto& [name, tx] : system.getTransformers()) {
      auto [p, s] = tx->getConnectedBuses();
      size_t i = busIdxMap[p];
      size_t j = busIdxMap[s];

      std::complex<double> y = 1.0 / tx->getImpedance();

      ybus(i, i) += y;
      ybus(j, j) += y;
      ybus(i, j) -= y;
      ybus(j, i) -= y;
    }

    for (const auto& [name, sourcePair] : system.getPowerSources()) {
      auto source = sourcePair.first;
      int busId = sourcePair.second;
      size_t i = busIdxMap[busId];

      std::complex<double> y = 1.0 / source->getImpedance();
      ybus(i, i) += y;
    }

    return ybus;
  }
};
}  // namespace powersim::core::analysis