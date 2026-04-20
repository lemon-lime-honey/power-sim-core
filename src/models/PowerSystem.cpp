#include "models/PowerSystem.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

#include "models/PowerSystem.hpp"

namespace powersim::models {

void PowerSystem::addBus(std::shared_ptr<Bus> bus) {
  buses_[bus->getId()] = bus;
}

void PowerSystem::addLine(std::shared_ptr<Line> line) {
  validateBuses(line->getConnectedBuses().first,
                line->getConnectedBuses().second);
  lines_[line->getName()] = line;
}

void PowerSystem::addTransformer(std::shared_ptr<Transformer> tx) {
  validateBuses(tx->getConnectedBuses().first, tx->getConnectedBuses().second);
  transformers_[tx->getName()] = tx;
}

void PowerSystem::addPowerSource(std::shared_ptr<PowerSource> source,
                                 int connectedBus) {
  if (!hasBus(connectedBus)) {
    throw std::invalid_argument(
        "Connected bus does not exist for PowerSource.");
  }
  powerSources_[source->getName()] = {source, connectedBus};
}

void PowerSystem::addReactor(std::shared_ptr<Reactor> reactor) {
  validateBuses(reactor->getConnectedBuses().first,
                reactor->getConnectedBuses().second);
  reactors_[reactor->getName()] = reactor;
}

void PowerSystem::addCapacitor(std::shared_ptr<Capacitor> capacitor) {
  validateBuses(capacitor->getConnectedBuses().first,
                capacitor->getConnectedBuses().second);
  capacitors_[capacitor->getName()] = capacitor;
}

void PowerSystem::addLoad(std::shared_ptr<Load> load) {
  if (!hasBus(load->getConnectedBus())) {
    throw std::invalid_argument("Connected bus does not exist for Load.");
  }
  loads_[load->getName()] = load;
}

void PowerSystem::addCircuitBreaker(std::shared_ptr<CircuitBreaker> cb) {
  cbs_[cb->getName()] = cb;
}

void PowerSystem::addDisconnectingSwitch(
    std::shared_ptr<DisconnectingSwitch> ds) {
  dss_[ds->getName()] = ds;
}

void PowerSystem::addCT(std::shared_ptr<CT> ct) { cts_[ct->getName()] = ct; }

void PowerSystem::addPT(std::shared_ptr<PT> pt) { pts_[pt->getName()] = pt; }

void PowerSystem::addRelay(std::shared_ptr<Relay> relay) {
  relays_[relay->getName()] = relay;
}

void PowerSystem::addLightningArrester(std::shared_ptr<LightningArrester> la) {
  las_[la->getName()] = la;
}

void PowerSystem::addMOF(std::shared_ptr<MOF> mof) {
  mofs_[mof->getName()] = mof;
}

void PowerSystem::attachCBToLine(const std::string& cbName,
                                 const std::string& lineName,
                                 bool isSendingEnd) {
  lineCBMapping_[lineName][isSendingEnd ? "S" : "R"] = cbName;
}

void PowerSystem::attachCTToLine(const std::string& ctName,
                                 const std::string& lineName) {
  lineCTMapping_[lineName] = ctName;
}

void PowerSystem::connectRelay(const std::string& relayName,
                               const std::string& ctName,
                               const std::string& cbName) {
  protectionMapping_[relayName] = {ctName, cbName};
}

std::shared_ptr<Bus> PowerSystem::getBus(int busId) const {
  auto it = buses_.find(busId);
  return it != buses_.end() ? it->second : nullptr;
}

std::shared_ptr<Line> PowerSystem::getLine(const std::string& name) const {
  auto it = lines_.find(name);
  return it != lines_.end() ? it->second : nullptr;
}

std::shared_ptr<CircuitBreaker> PowerSystem::getCircuitBreaker(
    const std::string& name) const {
  auto it = cbs_.find(name);
  return it != cbs_.end() ? it->second : nullptr;
}

std::shared_ptr<Relay> PowerSystem::getRelay(const std::string& name) const {
  auto it = relays_.find(name);
  return it != relays_.end() ? it->second : nullptr;
}

ConnectedEquipment PowerSystem::getConnectedEquipment(int busId) const {
  ConnectedEquipment eq;
  if (!hasBus(busId)) return eq;

  for (const auto& [name, line] : lines_) {
    auto buses = line->getConnectedBuses();
    if (buses.first == busId || buses.second == busId) eq.lines.push_back(line);
  }
  for (const auto& [name, tx] : transformers_) {
    auto buses = tx->getConnectedBuses();
    if (buses.first == busId || buses.second == busId)
      eq.transformers.push_back(tx);
  }
  for (const auto& [name, reactor] : reactors_) {
    auto buses = reactor->getConnectedBuses();
    if (buses.first == busId || (buses.second == busId && buses.second != 0))
      eq.reactors.push_back(reactor);
  }
  for (const auto& [name, capacitor] : capacitors_) {
    auto buses = capacitor->getConnectedBuses();
    if (buses.first == busId || (buses.second == busId && buses.second != 0))
      eq.capacitors.push_back(capacitor);
  }
  for (const auto& [name, load] : loads_) {
    if (load->getConnectedBus() == busId) eq.loads.push_back(load);
  }
  for (const auto& [name, sourcePair] : powerSources_) {
    if (sourcePair.second == busId) eq.powerSources.push_back(sourcePair.first);
  }

  return eq;
}

bool PowerSystem::hasBus(int busId) const {
  return buses_.find(busId) != buses_.end();
}

void PowerSystem::validateBuses(int fromBus, int toBus) const {
  if (!hasBus(fromBus) || (toBus != 0 && !hasBus(toBus))) {
    throw std::invalid_argument(
        "One or more connected buses do not exist in the system.");
  }
}

}  // namespace powersim::models