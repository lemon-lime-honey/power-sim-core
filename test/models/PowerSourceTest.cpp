#include <gtest/gtest.h>

#include <cmath>
#include <numbers>

#include "models/BaseSystem.hpp"
#include "models/PowerSource.hpp"

using namespace powersim::models;

class PowerSourceTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }

  PowerSource gridSource{"KEPCO_154kV", 154.0, 1000.0, 30.0};
  PowerSource infiniteBus{"Infinite_Bus", 22.9, 0.0, 0.0};
};

TEST_F(PowerSourceTest, CalculatesPhasorVoltageCorrectly) {
  auto phasor = gridSource.getPhasorVoltage();

  double v_phase = 154.0 / std::sqrt(3.0);
  double radians = 30.0 * std::numbers::pi / 180.0;

  EXPECT_DOUBLE_EQ(phasor.real(), v_phase * std::cos(radians));
  EXPECT_DOUBLE_EQ(phasor.imag(), v_phase * std::sin(radians));
}

TEST_F(PowerSourceTest, CalculatesImpedanceCorrectly) {
  auto z = gridSource.getImpedance();

  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_DOUBLE_EQ(z.imag(), 237.16);
}

TEST_F(PowerSourceTest, CalculatesPercentImpedanceUsingSystemBase) {
  auto percent_z = gridSource.getPercentImpedance();

  EXPECT_DOUBLE_EQ(percent_z.real(), 0.0);
  EXPECT_DOUBLE_EQ(percent_z.imag(), 10.0);
}

TEST_F(PowerSourceTest, HandlesInfiniteBusImpedance) {
  auto z = infiniteBus.getImpedance();
  auto percent_z = infiniteBus.getPercentImpedance();

  EXPECT_DOUBLE_EQ(z.imag(), 0.0);
  EXPECT_DOUBLE_EQ(percent_z.imag(), 0.0);
}