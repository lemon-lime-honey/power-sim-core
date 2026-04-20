#include <gtest/gtest.h>

#include <memory>

#include "models/PowerSystem.hpp"

using namespace powersim::models;

class PowerSystemTest : public ::testing::Test {
 protected:
  PowerSystem sys;

  void SetUp() override {
    sys.addBus(std::make_shared<Bus>(1, "Main_Bus", 22.9));
    sys.addBus(std::make_shared<Bus>(2, "Load_Bus", 22.9));
  }
};

TEST_F(PowerSystemTest, AddAndRetrieveBus) {
  auto bus = sys.getBus(1);
  ASSERT_NE(bus, nullptr);
  EXPECT_EQ(bus->getName(), "Main_Bus");

  auto nonExistentBus = sys.getBus(99);
  EXPECT_EQ(nonExistentBus, nullptr);
}

TEST_F(PowerSystemTest, ThrowsWhenAddingLineWithInvalidBus) {
  auto invalidLine = std::make_shared<Line>("Line1", 1, 99, 0.1, 0.2, 0.0, 0.0);
  EXPECT_THROW(sys.addLine(invalidLine), std::invalid_argument);
}

TEST_F(PowerSystemTest, RetrievesConnectedEquipmentAccurately) {
  auto line = std::make_shared<Line>("Line1", 1, 2, 0.1, 0.2, 0.0, 0.0);
  sys.addLine(line);

  auto load = std::make_shared<Load>("Load1", 2, 100.0, 50.0);
  sys.addLoad(load);

  ConnectedEquipment eqBus1 = sys.getConnectedEquipment(1);
  EXPECT_EQ(eqBus1.lines.size(), 1);
  EXPECT_EQ(eqBus1.loads.size(), 0);
  EXPECT_EQ(eqBus1.lines[0]->getName(), "Line1");

  ConnectedEquipment eqBus2 = sys.getConnectedEquipment(2);
  EXPECT_EQ(eqBus2.lines.size(), 1);
  EXPECT_EQ(eqBus2.loads.size(), 1);
  EXPECT_EQ(eqBus2.loads[0]->getName(), "Load1");
}

TEST_F(PowerSystemTest, MapsProtectionDevicesCorrectly) {
  sys.addCircuitBreaker(std::make_shared<CircuitBreaker>("CB_1", 25.8, 25.0));
  sys.addCT(std::make_shared<CT>("CT_1", 400.0, 5.0));
  sys.addRelay(std::make_shared<Relay>("OCR_1", RelayType::OCR, 5.0));
  sys.addLine(std::make_shared<Line>("Line_A", 1, 2, 0.1, 0.2, 0.0, 0.0));

  sys.attachCBToLine("CB_1", "Line_A", true);
  sys.attachCTToLine("CT_1", "Line_A");
  sys.connectRelay("OCR_1", "CT_1", "CB_1");

  auto retrievedCB = sys.getCircuitBreaker("CB_1");
  ASSERT_NE(retrievedCB, nullptr);
  EXPECT_EQ(retrievedCB->getRatedVoltage(), 25.8);

  auto retrievedRelay = sys.getRelay("OCR_1");
  ASSERT_NE(retrievedRelay, nullptr);
  EXPECT_EQ(retrievedRelay->getType(), RelayType::OCR);
}