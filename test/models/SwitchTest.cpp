#include <gtest/gtest.h>

#include "models/Switch.hpp"

using namespace powersim::models;

class SwitchTest : public ::testing::Test {
 protected:
  Switch testSwitch{"Main_Switch"};
};

TEST_F(SwitchTest, InitializesAsClosedByDefault) {
  EXPECT_EQ(testSwitch.getName(), "Main_Switch");
  EXPECT_TRUE(testSwitch.isClosed());
}

TEST_F(SwitchTest, TogglesStateCorrectly) {
  testSwitch.open();
  EXPECT_FALSE(testSwitch.isClosed());

  testSwitch.close();
  EXPECT_TRUE(testSwitch.isClosed());
}

TEST_F(SwitchTest, CanInitializeAsOpen) {
  Switch openSwitch{"Open_Switch", false};
  EXPECT_FALSE(openSwitch.isClosed());
}