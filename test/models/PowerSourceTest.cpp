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

TEST_F(PowerSourceTest, CalculatesImpedancePU) {
  auto z = gridSource.getImpedance();
  // 1000 MVA 단락용량, 100 MVA 기준 -> Z_pu = 100/1000 = 0.1
  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_DOUBLE_EQ(z.imag(), 0.1);
}

TEST_F(PowerSourceTest, HandlesInfiniteBusImpedance) {
  auto z = infiniteBus.getImpedance();
  EXPECT_DOUBLE_EQ(z.imag(), 0.0);
}