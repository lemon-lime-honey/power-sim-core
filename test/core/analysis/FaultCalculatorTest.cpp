#include <gtest/gtest.h>

#include <cmath>
#include <complex>
#include <numbers>

#include "core/analysis/FaultCalculator.hpp"
#include "core/analysis/ThreePhaseFault.hpp"
#include "models/BaseSystem.hpp"
#include "models/PowerSystem.hpp"

using namespace powersim::models;
using namespace powersim::core::analysis;

class FaultCalculatorTest : public ::testing::Test {
 protected:
  PowerSystem sys;

  void SetUp() override {
    BaseSystem::instance().setBase(60.0, 100.0);

    sys.addBus(std::make_shared<Bus>(1, "Main_Bus", 22.9));
    sys.addBus(std::make_shared<Bus>(2, "Load_Bus", 22.9));

    auto source = std::make_shared<PowerSource>("KEPCO", 22.9, 1000.0);
    sys.addPowerSource(source, 1);

    double zBase = 22.9 * 22.9 / 100.0;
    double xOhm = 0.1 * zBase;
    double lHenry = xOhm / (2.0 * std::numbers::pi * 60.0);

    auto line =
        std::make_shared<Line>("Line1", 1, 2, 22.9, 0.0, lHenry, 0.0, 0.0);
    sys.addLine(line);

    sys.addCircuitBreaker(
        std::make_shared<CircuitBreaker>("Strong_CB", 25.8, 25.0));
    sys.addCircuitBreaker(
        std::make_shared<CircuitBreaker>("Weak_CB", 25.8, 8.0));
  }
};

TEST_F(FaultCalculatorTest, CalculatesFaultCurrentAndCapacity) {
  ThreePhaseFault fault3P;
  FaultReport report = FaultCalculator::calculate(sys, 2, fault3P);

  double expectedZMag = 0.2;
  double expectedCapacity = 500.0;
  double expectedCurrent = 500.0 / (std::sqrt(3.0) * 22.9);

  EXPECT_EQ(report.faultBusId, 2);
  EXPECT_NEAR(std::abs(report.theveninImpedance), expectedZMag, 1e-6);
  EXPECT_NEAR(report.faultCapacity, expectedCapacity, 1e-4);
  EXPECT_NEAR(report.faultCurrent, expectedCurrent, 1e-4);
}

TEST_F(FaultCalculatorTest, EvaluatesBreakerSafetyCorrectly) {
  ThreePhaseFault fault3P;
  FaultReport report = FaultCalculator::calculate(sys, 2, fault3P);

  bool isStrongSafe = FaultCalculator::evaluateBreakerSafety(
      sys, "Strong_CB", report.faultCapacity);
  EXPECT_TRUE(isStrongSafe);

  bool isWeakSafe = FaultCalculator::evaluateBreakerSafety(
      sys, "Weak_CB", report.faultCapacity);
  EXPECT_FALSE(isWeakSafe);
}

TEST_F(FaultCalculatorTest, ThrowsExceptionForInvalidBus) {
  ThreePhaseFault fault3P;
  EXPECT_THROW(FaultCalculator::calculate(sys, 999, fault3P),
               std::invalid_argument);
}