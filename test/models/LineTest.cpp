#include <gtest/gtest.h>

#include <numbers>

#include "models/BaseSystem.hpp"
#include "models/Line.hpp"

using namespace powersim::models;

class LineTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }

  Line testLine{"TL_01", 1, 2, 0.1, 0.01, 0.0, 1e-6};
};

TEST_F(LineTest, CalculatesImpedanceUsingSystemFrequency) {
  auto z = testLine.getImpedance();

  double expected_x = 2.0 * std::numbers::pi * 60.0 * 0.01;

  EXPECT_DOUBLE_EQ(z.real(), 0.1);
  EXPECT_NEAR(z.imag(), expected_x, 1e-6);
}

TEST_F(LineTest, CalculatesAdmittanceUsingSystemFrequency) {
  auto y = testLine.getAdmittance();

  double expected_b = 2.0 * std::numbers::pi * 60.0 * 1e-6;

  EXPECT_DOUBLE_EQ(y.real(), 0.0);
  EXPECT_NEAR(y.imag(), expected_b, 1e-9);
}

TEST_F(LineTest, ReturnsCorrectConnectedBuses) {
  auto buses = testLine.getConnectedBuses();
  EXPECT_EQ(buses.first, 1);
  EXPECT_EQ(buses.second, 2);
}