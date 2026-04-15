#include <gtest/gtest.h>

#include "models/LightningArrester.hpp"

using namespace powersim::models;

TEST(LightningArresterTest, HoldsNameplateDataCorrectly) {
  LightningArrester la{"Main_LA", 18.0, 2.5, 65.0};

  EXPECT_EQ(la.getName(), "Main_LA");
  EXPECT_DOUBLE_EQ(la.getRatedVoltage(), 18.0);
  EXPECT_DOUBLE_EQ(la.getNominalDischargeCurrent(), 2.5);
  EXPECT_DOUBLE_EQ(la.getResidualVoltage(), 65.0);
}