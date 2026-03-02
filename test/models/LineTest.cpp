#include <gtest/gtest.h>

#include <numbers>

#include "models/Line.hpp"

using namespace powersim::models;

class LineTest : public ::testing::Test {
 protected:
  Line testLine{"TL_01", 1, 2, 0.1, 0.01, 0.0, 1e-6};
};

TEST_F(LineTest, CalculatesImpedanceAt60Hz) {
  auto z = testLine.getImpedance(60.0);

  double expected_x = 2.0 * std::numbers::pi * 60.0 * 0.01;

  EXPECT_DOUBLE_EQ(z.real(), 0.1);
  EXPECT_NEAR(z.imag(), expected_x, 1e-6);
}

TEST_F(LineTest, CalculatesAdmittanceAt60Hz) {
  auto y = testLine.getAdmittance(60.0);

  double expected_b = 2.0 * std::numbers::pi * 60.0 * 1e-6;

  EXPECT_DOUBLE_EQ(y.real(), 0.0);
  EXPECT_NEAR(y.imag(), expected_b, 1e-9);
}

TEST_F(LineTest, ReturnsCorrectConnectedNodes) {
  auto buses = testLine.getConnectedNodes();
  EXPECT_EQ(buses.first, 1);
  EXPECT_EQ(buses.second, 2);
}