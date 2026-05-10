#include <gtest/gtest.h>

#include "core/analysis/ProtectionCoordinator.hpp"
#include "core/analysis/TripCurve.hpp"
#include "models/PowerSystem.hpp"

using namespace powersim::models;
using namespace powersim::core::analysis;

class ProtectionCoordinatorTest : public ::testing::Test {
 protected:
  PowerSystem sys;
  StandardInverseCurve iecCurve;

  void SetUp() override {
    sys.addCircuitBreaker(
        std::make_shared<CircuitBreaker>("CB_Main", 25.8, 25.0));
    sys.addCT(std::make_shared<CT>("CT_Main", 400.0, 5.0));
    sys.addRelay(
        std::make_shared<Relay>("OCR_Main", RelayType::OCR, 5.0, 10.0));
    sys.connectRelay("OCR_Main", "CT_Main", "CB_Main");
  }
};

TEST_F(ProtectionCoordinatorTest, SimulatesTripCorrectlyOnHighFaultCurrent) {
  TripEvent event =
      ProtectionCoordinator::simulate(sys, "OCR_Main", 4.0, iecCurve);

  EXPECT_TRUE(event.tripped);
  EXPECT_EQ(event.relayName, "OCR_Main");
  EXPECT_EQ(event.cbName, "CB_Main");
  EXPECT_NEAR(event.tripTime, 29.702, 1e-3);

  auto cb = sys.getCircuitBreaker("CB_Main");
  EXPECT_FALSE(cb->isClosed());
}

TEST_F(ProtectionCoordinatorTest, IgnoresNormalLoadCurrent) {
  TripEvent event =
      ProtectionCoordinator::simulate(sys, "OCR_Main", 0.3, iecCurve);

  EXPECT_FALSE(event.tripped);
  EXPECT_EQ(event.tripTime, 0.0);

  auto cb = sys.getCircuitBreaker("CB_Main");
  EXPECT_TRUE(cb->isClosed());
}