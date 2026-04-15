#include <gtest/gtest.h>

#include "models/InstrumentTransformer.hpp"

using namespace powersim::models;

class InstrumentTransformerTest : public ::testing::Test {
 protected:
  InstrumentTransformer testTransformer{"Test_IT", 500.0, 5.0};
};

TEST_F(InstrumentTransformerTest, CalculatesRatioCorrectly) {
  EXPECT_DOUBLE_EQ(testTransformer.getRatio(), 100.0);
}

TEST_F(InstrumentTransformerTest, ReturnsRatedValues) {
  EXPECT_EQ(testTransformer.getName(), "Test_IT");
  EXPECT_DOUBLE_EQ(testTransformer.getPrimaryValue(), 500.0);
  EXPECT_DOUBLE_EQ(testTransformer.getSecondaryValueRated(), 5.0);
}