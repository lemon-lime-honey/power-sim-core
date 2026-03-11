#include <gtest/gtest.h>

#include <cmath>
#include <numbers>

#include "models/PowerSource.hpp"

using namespace powersim::models;

class PowerSourceTest : public ::testing::Test {
 protected:
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

TEST_F(PowerSourceTest, CalculatesSourceImpedanceOhm) {
  auto z_ohm = gridSource.getSourceImpedanceOhm();

  EXPECT_DOUBLE_EQ(z_ohm.real(), 0.0);
  EXPECT_DOUBLE_EQ(z_ohm.imag(), 23.716);
}

TEST_F(PowerSourceTest, CalculatesPercentImpedance) {
  double baseMVA = 100.0;
  auto percent_z = gridSource.getPercentImpedance(baseMVA);

  EXPECT_DOUBLE_EQ(percent_z.real(), 0.0);
  EXPECT_DOUBLE_EQ(percent_z.imag(), 10.0);
}

TEST_F(PowerSourceTest, HandlesInfiniteBusImpedance) {
  auto z_ohm = infiniteBus.getSourceImpedanceOhm();
  auto percent_z = infiniteBus.getPercentImpedance(100.0);

  EXPECT_DOUBLE_EQ(z_ohm.real(), 0.0);
  EXPECT_DOUBLE_EQ(z_ohm.imag(), 0.0);
  EXPECT_DOUBLE_EQ(percent_z.real(), 0.0);
  EXPECT_DOUBLE_EQ(percent_z.imag(), 0.0);
}