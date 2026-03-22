#include <gtest/gtest.h>

#include <cmath>

#include "models/Load.hpp"

using namespace powersim::models;

class LoadTest : public ::testing::Test {
 protected:
  Load typicalLoad{"Motor_A", 1, 80.0, 60.0, LoadType::Motor};
  Load resistiveLoad{"Heater_A", 2, 100.0, 0.0, LoadType::General};
};

TEST_F(LoadTest, CalculatesApparentPowerCorrectly) {
  EXPECT_DOUBLE_EQ(typicalLoad.getApparentPower(), 100.0);
  EXPECT_DOUBLE_EQ(resistiveLoad.getApparentPower(), 100.0);
}

TEST_F(LoadTest, CalculatesPowerFactorCorrectly) {
  EXPECT_DOUBLE_EQ(typicalLoad.getPowerFactor(), 0.8);
  EXPECT_DOUBLE_EQ(resistiveLoad.getPowerFactor(), 1.0);
}

TEST_F(LoadTest, ReturnsComplexPower) {
  auto complexPower = typicalLoad.getComplexPower();
  EXPECT_DOUBLE_EQ(complexPower.real(), 80.0);
  EXPECT_DOUBLE_EQ(complexPower.imag(), 60.0);
}

TEST_F(LoadTest, HandlesZeroLoad) {
  Load zeroLoad{"Empty", 3, 0.0, 0.0};
  EXPECT_DOUBLE_EQ(zeroLoad.getApparentPower(), 0.0);
  EXPECT_DOUBLE_EQ(zeroLoad.getPowerFactor(), 1.0);
}

TEST_F(LoadTest, ReturnsConnectedBus) {
  EXPECT_EQ(typicalLoad.getConnectedBus(), 1);
  EXPECT_EQ(resistiveLoad.getConnectedBus(), 2);
}