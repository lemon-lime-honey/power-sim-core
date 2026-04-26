#include <gtest/gtest.h>

#include <numbers>

#include "models/BaseSystem.hpp"
#include "models/Line.hpp"

using namespace powersim::models;

class LineTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }
  Line testLine{"TL_01", 1, 2, 154.0, 0.1, 0.01, 0.0, 1e-6};
};

TEST_F(LineTest, CalculatesImpedancePU) {
  auto z = testLine.getImpedance();
  double z_base = 154.0 * 154.0 / 100.0;  // 237.16
  double expected_r_pu = 0.1 / z_base;
  double expected_x_pu = (2.0 * std::numbers::pi * 60.0 * 0.01) / z_base;

  EXPECT_DOUBLE_EQ(z.real(), expected_r_pu);
  EXPECT_NEAR(z.imag(), expected_x_pu, 1e-6);
}

TEST_F(LineTest, CalculatesAdmittancePU) {
  auto y = testLine.getAdmittance();
  double z_base = 154.0 * 154.0 / 100.0;
  double expected_b_siemens = 2.0 * std::numbers::pi * 60.0 * 1e-6;
  double expected_b_pu = expected_b_siemens * z_base;

  EXPECT_DOUBLE_EQ(y.real(), 0.0);
  EXPECT_NEAR(y.imag(), expected_b_pu, 1e-9);
}