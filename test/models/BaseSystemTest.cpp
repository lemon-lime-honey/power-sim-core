#include <gtest/gtest.h>

#include "models/BaseSystem.hpp"

using namespace powersim::models;

class BaseSystemTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }
};

TEST_F(BaseSystemTest, ShouldStoreBaseValuesCorrectly) {
  auto& base = BaseSystem::instance();
  base.setBase(50.0, 200.0);
  EXPECT_DOUBLE_EQ(base.getFrequency(), 50.0);
  EXPECT_DOUBLE_EQ(base.getBasePower(), 200.0);
}

TEST_F(BaseSystemTest, ShouldCalculateBaseImpedanceProperly) {
  auto& base = BaseSystem::instance();
  base.setBase(60.0, 100.0);

  double z_base_154 = base.getBaseImpedance(154.0);
  EXPECT_NEAR(z_base_154, 237.16, 1e-9);

  double z_base_229 = base.getBaseImpedance(22.9);
  EXPECT_NEAR(z_base_229, 5.2441, 1e-9);
}

TEST_F(BaseSystemTest, ShouldReturnZeroWhenBasePowerIsZero) {
  auto& base = BaseSystem::instance();
  base.setBase(60.0, 0.0);
  EXPECT_DOUBLE_EQ(base.getBaseImpedance(154.0), 0.0);
}