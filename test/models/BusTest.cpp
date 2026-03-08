#include <gtest/gtest.h>

#include <memory>

#include "models/Bus.hpp"
#include "models/Line.hpp"
#include "models/Load.hpp"

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

TEST_F(BusTest, ManagesConnectedTopology) {
  auto load = std::make_shared<Load>("Load_1", 100.0, 50.0);
  auto line = std::make_shared<Line>("Line_1", 1, 2, 0.1, 0.01, 0.0, 0.0);

  testBus.addLoad(load);
  testBus.addLine(line);

  ASSERT_EQ(testBus.getLoads().size(), 1);
  EXPECT_EQ(testBus.getLoads()[0]->getName(), "Load_1");

  ASSERT_EQ(testBus.getLines().size(), 1);
  EXPECT_EQ(testBus.getLines()[0]->getName(), "Line_1");
}