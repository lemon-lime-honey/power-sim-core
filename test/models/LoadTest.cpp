#include <gtest/gtest.h>

#include <cmath>

#include "models/BaseSystem.hpp"
#include "models/Load.hpp"

using namespace powersim::models;

class LoadTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }
  Load typicalLoad{"Motor_A", 1, 80.0, 60.0, LoadType::Motor};
};

TEST_F(LoadTest, CalculatesPowerPU) {
  EXPECT_DOUBLE_EQ(typicalLoad.getActivePower(), 0.8);
  EXPECT_DOUBLE_EQ(typicalLoad.getReactivePower(), 0.6);
  EXPECT_DOUBLE_EQ(typicalLoad.getApparentPower(), 1.0);  // sqrt(0.8^2 + 0.6^2)

  EXPECT_DOUBLE_EQ(typicalLoad.getPowerFactor(), 0.8);
}