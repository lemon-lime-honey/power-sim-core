#include <gtest/gtest.h>

#include <complex>

#include "models/Transformer.hpp"

using namespace powersim::models;

class TransformerTest : public ::testing::Test {
 protected:
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

TEST_F(TransformerTest, ScalesPercentImpedanceByBaseMva) {
  double systemBaseMva = 100.0;
  auto scaledImpedance = stepDownTx.getPercentImpedance(systemBaseMva);

  EXPECT_DOUBLE_EQ(scaledImpedance.real(), 0.0);
  EXPECT_NEAR(scaledImpedance.imag(), 16.666666666666668, 1e-9);
}

TEST_F(TransformerTest, HandlesZeroCapacityGracefully) {
  Transformer zeroCapTx{"Zero_Cap", 3, 4, 0.0, 22.9, 380.0, {0.0, 5.0}};
  auto result = zeroCapTx.getPercentImpedance(100.0);

  EXPECT_DOUBLE_EQ(result.real(), 0.0);
  EXPECT_DOUBLE_EQ(result.imag(), 0.0);
}