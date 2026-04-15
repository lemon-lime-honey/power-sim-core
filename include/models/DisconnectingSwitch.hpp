#pragma once

#include <string>

#include "Switch.hpp"

namespace powersim::models {

class DisconnectingSwitch : public Switch {
 public:
  DisconnectingSwitch(std::string name, bool isClosed = true)
      : Switch(std::move(name), isClosed) {}
};

}  // namespace powersim::models