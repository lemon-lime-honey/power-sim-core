#include <gtest/gtest.h>

#include "models/PT.hpp"

using namespace powersim::models;

TEST(PTTest, InitializesWithDefaultSecondaryVoltage) {
  PT pt{"Main_PT", 22900.0};

  EXPECT_EQ(pt.getName(), "Main_PT");
  EXPECT_DOUBLE_EQ(pt.getPrimaryValue(), 22900.0);
  EXPECT_DOUBLE_EQ(pt.getSecondaryValueRated(), 110.0);
  EXPECT_DOUBLE_EQ(pt.getRatio(), 22900.0 / 110.0);
}