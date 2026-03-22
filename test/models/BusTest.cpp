#include <gtest/gtest.h>

#include "models/Bus.hpp"

using namespace powersim::models;

class BusTest : public ::testing::Test {
 protected:
  Bus testBus{1, "Main_Bus", 22.9};
};

TEST_F(BusTest, InitializesCorrectly) {
  EXPECT_EQ(testBus.getId(), 1);
  EXPECT_EQ(testBus.getName(), "Main_Bus");
  EXPECT_DOUBLE_EQ(testBus.getNominalVoltage(), 22.9);
}