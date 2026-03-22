#pragma once

#include <utility>
#include <vector>

#include "Bus.hpp"
#include "Capacitor.hpp"
#include "Line.hpp"
#include "Load.hpp"
#include "PowerSource.hpp"
#include "Reactor.hpp"
#include "Transformer.hpp"

namespace powersim::models {
struct ConnectedEquipment {
  std::vector<const Line*> lines;
  std::vector<const Transformer*> transformers;
  std::vector<const Reactor*> reactors;
  std::vector<const Capacitor*> capacitors;
  std::vector<const Load*> loads;
  std::vector<const PowerSource*> powerSources;
};

class PowerSystem {
 public:
  PowerSystem() = default;

  void addBus(const Bus& bus);
  void addLine(const Line& line);
  void addTransformer(const Transformer& tx);
  void addPowerSource(const PowerSource& source, int connectedBus);
  void addReactor(const Reactor& reactor);
  void addCapacitor(const Capacitor& capacitor);
  void addLoad(const Load& load);

  const std::vector<Bus>& getBuses() const { return buses_; }
  const std::vector<Line>& getLines() const { return lines_; }
  const std::vector<Transformer>& getTransformers() const {
    return transformers_;
  }
  const std::vector<std::pair<PowerSource, int>>& getPowerSources() const {
    return powerSources_;
  }
  const std::vector<Reactor>& getReactors() const { return reactors_; }
  const std::vector<Capacitor>& getCapacitors() const { return capacitors_; }
  const std::vector<Load>& getLoads() const { return loads_; }

  ConnectedEquipment getConnectedEquipment(int busId) const;

 private:
  std::vector<Bus> buses_;
  std::vector<Line> lines_;
  std::vector<Transformer> transformers_;
  std::vector<std::pair<PowerSource, int>> powerSources_;
  std::vector<Reactor> reactors_;
  std::vector<Capacitor> capacitors_;
  std::vector<Load> loads_;

  bool hasBus(int busId) const;
  void validateBuses(int fromBus, int toBus) const;
};
}  // namespace powersim::models