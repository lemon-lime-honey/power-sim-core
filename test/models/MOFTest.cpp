#include <gtest/gtest.h>

#include "models/MOF.hpp"

using namespace powersim::models;

TEST(MOFTest, ComposesPTAndCTCorrectly) {
  MOF mof{"Main_MOF", 22900.0, 100.0, 110.0, 5.0};

  EXPECT_EQ(mof.getName(), "Main_MOF");

  auto pt = mof.getPT();
  EXPECT_EQ(pt.getName(), "Main_MOF_PT");
  EXPECT_DOUBLE_EQ(pt.getPrimaryValue(), 22900.0);
  EXPECT_DOUBLE_EQ(pt.getSecondaryValueRated(), 110.0);

  auto ct = mof.getCT();
  EXPECT_EQ(ct.getName(), "Main_MOF_CT");
  EXPECT_DOUBLE_EQ(ct.getPrimaryValue(), 100.0);
  EXPECT_DOUBLE_EQ(ct.getSecondaryValueRated(), 5.0);
}

TEST(MOFTest, UsesDefaultSecondaryValues) {
  MOF mof{"Default_MOF", 22900.0, 50.0};

  EXPECT_DOUBLE_EQ(mof.getPT().getSecondaryValueRated(), 110.0);
  EXPECT_DOUBLE_EQ(mof.getCT().getSecondaryValueRated(), 5.0);
}