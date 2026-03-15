#include <gtest/gtest.h>

#include <complex>

#include "models/BaseSystem.hpp"
#include "models/Transformer.hpp"

using namespace powersim::models;

class TransformerTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }

  Transformer stepDownTx{"MTR_01", 1, 2, 60.0, 154.0, 22.9, {0.0, 10.0}};
};

TEST_F(TransformerTest, InitializesAttributesCorrectly) {
  EXPECT_EQ(stepDownTx.getName(), "MTR_01");
  EXPECT_DOUBLE_EQ(stepDownTx.getRatedPower(), 60.0);
  EXPECT_DOUBLE_EQ(stepDownTx.getPrimaryVoltage(), 154.0);
  EXPECT_DOUBLE_EQ(stepDownTx.getSecondaryVoltage(), 22.9);

  auto buses = stepDownTx.getConnectedBuses();
  EXPECT_EQ(buses.first, 1);
  EXPECT_EQ(buses.second, 2);
}

TEST_F(TransformerTest, CalculatesImpedanceCorrectly) {
  auto z = stepDownTx.getImpedance();

  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_NEAR(z.imag(), 395.26666666666665, 1e-9);
}

TEST_F(TransformerTest, CalculatesPercentImpedanceUsingSystemBase) {
  auto scaledImpedance = stepDownTx.getPercentImpedance();

  EXPECT_DOUBLE_EQ(scaledImpedance.real(), 0.0);
  EXPECT_NEAR(scaledImpedance.imag(), 16.666666666666668, 1e-9);
}

TEST_F(TransformerTest, HandlesZeroCapacityGracefully) {
  Transformer zeroCapTx{"Zero_Cap", 3, 4, 0.0, 22.9, 380.0, {0.0, 5.0}};

  auto z = zeroCapTx.getImpedance();
  auto percent_z = zeroCapTx.getPercentImpedance();

  EXPECT_DOUBLE_EQ(z.imag(), 0.0);
  EXPECT_DOUBLE_EQ(percent_z.imag(), 0.0);
}