#include "models/PowerSystem.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

namespace powersim::models {
void PowerSystem::addBus(const Bus& bus) {
  if (hasBus(bus.getId())) {
    throw std::invalid_argument("Bus ID " + std::to_string(bus.getId()) +
                                " already exists.");
  }
  buses_.push_back(bus);
}

void PowerSystem::addLine(const Line& line) {
  validateNodes(line.getConnectedNodes().first,
                line.getConnectedNodes().second);
  lines_.push_back(line);
}

void PowerSystem::addTransformer(const Transformer& tx) {
  validateNodes(tx.getConnectedBuses().first, tx.getConnectedBuses().second);
  transformers_.push_back(tx);
}

void PowerSystem::addPowerSource(const PowerSource& source, int connectedBus) {
  validateNodes(connectedBus, 0);
  powerSources_.push_back({source, connectedBus});
}

void PowerSystem::addReactor(const Reactor& reactor) {
  validateNodes(reactor.getConnectedBuses().first,
                reactor.getConnectedBuses().second);
  reactors_.push_back(reactor);
}

void PowerSystem::addCapacitor(const Capacitor& capacitor) {
  validateNodes(capacitor.getConnectedBuses().first,
                capacitor.getConnectedBuses().second);
  capacitors_.push_back(capacitor);
}

void PowerSystem::addLoad(const Load& load) {
  validateNodes(load.getConnectedBus(), 0);
  loads_.push_back(load);
}

ConnectedEquipment PowerSystem::getConnectedEquipment(int busId) const {
  ConnectedEquipment eq;

  for (const auto& line : lines_) {
    auto nodes = line.getConnectedNodes();
    if (nodes.first == busId || nodes.second == busId) {
      eq.lines.push_back(&line);
    }
  }

  for (const auto& transformer : transformers_) {
    auto nodes = transformer.getConnectedBuses();
    if (nodes.first == busId || nodes.second == busId) {
      eq.transformers.push_back(&transformer);
    }
  }

  for (const auto& reactor : reactors_) {
    auto nodes = reactor.getConnectedBuses();
    if (nodes.first == busId || nodes.second == busId) {
      eq.reactors.push_back(&reactor);
    }
  }

  for (const auto& cap : capacitors_) {
    auto nodes = cap.getConnectedBuses();
    if (nodes.first == busId || nodes.second == busId) {
      eq.capacitors.push_back(&cap);
    }
  }

  for (const auto& load : loads_) {
    if (load.getConnectedBus() == busId) {
      eq.loads.push_back(&load);
    }
  }

  for (const auto& pair : powerSources_) {
    if (pair.second == busId) {
      eq.powerSources.push_back(&pair.first);
    }
  }

  return eq;
}

bool PowerSystem::hasBus(int busId) const {
  return std::any_of(buses_.begin(), buses_.end(),
                     [busId](const Bus& b) { return b.getId() == busId; });
}

void PowerSystem::validateNodes(int fromBus, int toBus) const {
  auto checkNode = [this](int nodeId) {
    if (nodeId == 0) return;
    if (!hasBus(nodeId)) {
      throw std::invalid_argument("Node validation failed: Bus ID " +
                                  std::to_string(nodeId) + " not found.");
    }
  };
  checkNode(fromBus);
  checkNode(toBus);
}
}  // namespace powersim::models