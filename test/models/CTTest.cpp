#include <gtest/gtest.h>

#include "models/CT.hpp"

using namespace powersim::models;

TEST(CTTest, InitializesWithDefaultSecondaryCurrent) {
  CT ct{"Main_CT", 400.0};

  EXPECT_EQ(ct.getName(), "Main_CT");
  EXPECT_DOUBLE_EQ(ct.getPrimaryValue(), 400.0);
  EXPECT_DOUBLE_EQ(ct.getSecondaryValueRated(), 5.0);
  EXPECT_DOUBLE_EQ(ct.getRatio(), 80.0);
}