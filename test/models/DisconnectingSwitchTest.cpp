#include <gtest/gtest.h>

#include "models/DisconnectingSwitch.hpp"

using namespace powersim::models;

TEST(DisconnectingSwitchTest, InheritsSwitchBehavior) {
  DisconnectingSwitch ds{"Main_DS"};

  EXPECT_EQ(ds.getName(), "Main_DS");
  EXPECT_TRUE(ds.isClosed());

  ds.open();
  EXPECT_FALSE(ds.isClosed());
}