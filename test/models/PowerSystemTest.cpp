#include <gtest/gtest.h>

#include <stdexcept>

#include "models/Bus.hpp"
#include "models/Line.hpp"
#include "models/PowerSystem.hpp"
#include "models/Reactor.hpp"

using namespace powersim::models;

class PowerSystemTest : public ::testing::Test {
 protected:
  PowerSystem system;

  void SetUp() override {
    system.addBus(Bus{1, "Bus_1", 154.0});
    system.addBus(Bus{2, "Bus_2", 154.0});
  }
};

TEST_F(PowerSystemTest, PreventsDuplicateBusId) {
  EXPECT_THROW(system.addBus(Bus{1, "Duplicate", 22.9}), std::invalid_argument);
}

TEST_F(PowerSystemTest, AddsValidDevicesSuccessfully) {
  Line validLine{"Line_1_2", 1, 2, 0.01, 0.02, 0.0, 1e-6};

  EXPECT_NO_THROW(system.addLine(validLine));
  EXPECT_EQ(system.getLines().size(), 1);
}

TEST_F(PowerSystemTest, ThrowsWhenConnectingToInvalidBus) {
  Line invalidLine{"Line_2_3", 2, 3, 0.01, 0.02, 0.0, 1e-6};

  EXPECT_THROW(system.addLine(invalidLine), std::invalid_argument);
}

TEST_F(PowerSystemTest, AllowsShuntConnectionToGround) {
  Reactor shuntReactor{"Shunt_1", 1, 0, 154.0, 50.0};

  EXPECT_NO_THROW(system.addReactor(shuntReactor));
  EXPECT_EQ(system.getReactors().size(), 1);
}