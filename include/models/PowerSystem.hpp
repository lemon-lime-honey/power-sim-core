#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Bus.hpp"
#include "CT.hpp"
#include "Capacitor.hpp"
#include "CircuitBreaker.hpp"
#include "DisconnectingSwitch.hpp"
#include "LightningArrester.hpp"
#include "Line.hpp"
#include "Load.hpp"
#include "MOF.hpp"
#include "PT.hpp"
#include "PowerSource.hpp"
#include "Reactor.hpp"
#include "Relay.hpp"
#include "Transformer.hpp"

namespace powersim::models {

struct ConnectedEquipment {
  std::vector<std::shared_ptr<Line>> lines;
  std::vector<std::shared_ptr<Transformer>> transformers;
  std::vector<std::shared_ptr<Reactor>> reactors;
  std::vector<std::shared_ptr<Capacitor>> capacitors;
  std::vector<std::shared_ptr<Load>> loads;
  std::vector<std::shared_ptr<PowerSource>> powerSources;
};

class PowerSystem {
 public:
  PowerSystem() = default;

  void addBus(std::shared_ptr<Bus> bus);
  void addLine(std::shared_ptr<Line> line);
  void addTransformer(std::shared_ptr<Transformer> tx);
  void addPowerSource(std::shared_ptr<PowerSource> source, int connectedBus);
  void addReactor(std::shared_ptr<Reactor> reactor);
  void addCapacitor(std::shared_ptr<Capacitor> capacitor);
  void addLoad(std::shared_ptr<Load> load);

  void addCircuitBreaker(std::shared_ptr<CircuitBreaker> cb);
  void addDisconnectingSwitch(std::shared_ptr<DisconnectingSwitch> ds);
  void addCT(std::shared_ptr<CT> ct);
  void addPT(std::shared_ptr<PT> pt);
  void addRelay(std::shared_ptr<Relay> relay);
  void addLightningArrester(std::shared_ptr<LightningArrester> la);
  void addMOF(std::shared_ptr<MOF> mof);

  void attachCBToLine(const std::string& cbName, const std::string& lineName,
                      bool isSendingEnd = true);
  void attachCTToLine(const std::string& ctName, const std::string& lineName);
  void connectRelay(const std::string& relayName, const std::string& ctName,
                    const std::string& cbName);

  std::shared_ptr<Bus> getBus(int busId) const;
  std::shared_ptr<Line> getLine(const std::string& name) const;
  std::shared_ptr<CircuitBreaker> getCircuitBreaker(
      const std::string& name) const;
  std::shared_ptr<Relay> getRelay(const std::string& name) const;

  ConnectedEquipment getConnectedEquipment(int busId) const;

 private:
  std::map<int, std::shared_ptr<Bus>> buses_;

  std::map<std::string, std::shared_ptr<Line>> lines_;
  std::map<std::string, std::shared_ptr<Transformer>> transformers_;
  std::map<std::string, std::pair<std::shared_ptr<PowerSource>, int>>
      powerSources_;
  std::map<std::string, std::shared_ptr<Reactor>> reactors_;
  std::map<std::string, std::shared_ptr<Capacitor>> capacitors_;
  std::map<std::string, std::shared_ptr<Load>> loads_;

  std::map<std::string, std::shared_ptr<CircuitBreaker>> cbs_;
  std::map<std::string, std::shared_ptr<DisconnectingSwitch>> dss_;
  std::map<std::string, std::shared_ptr<CT>> cts_;
  std::map<std::string, std::shared_ptr<PT>> pts_;
  std::map<std::string, std::shared_ptr<Relay>> relays_;
  std::map<std::string, std::shared_ptr<LightningArrester>> las_;
  std::map<std::string, std::shared_ptr<MOF>> mofs_;

  std::map<std::string, std::map<std::string, std::string>> lineCBMapping_;
  std::map<std::string, std::string> lineCTMapping_;

  struct ProtectionLink {
    std::string ctName;
    std::string cbName;
  };
  std::map<std::string, ProtectionLink> protectionMapping_;

  bool hasBus(int busId) const;
  void validateBuses(int fromBus, int toBus) const;
};

}  // namespace powersim::models