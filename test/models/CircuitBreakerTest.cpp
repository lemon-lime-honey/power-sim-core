#include <gtest/gtest.h>

#include <cmath>

#include "models/CircuitBreaker.hpp"

using namespace powersim::models;

TEST(CircuitBreakerTest, CalculatesBreakingCapacityCorrectly) {
  CircuitBreaker cb{"Main_CB", 25.8, 25.0};  // 25.8kV, 25kA 차단기

  EXPECT_EQ(cb.getName(), "Main_CB");
  EXPECT_DOUBLE_EQ(cb.getRatedVoltage(), 25.8);
  EXPECT_DOUBLE_EQ(cb.getRatedBreakingCurrent(), 25.0);

  double expectedCapacity = std::sqrt(3.0) * 25.8 * 25.0;
  EXPECT_DOUBLE_EQ(cb.getBreakingCapacity(), expectedCapacity);
}

TEST(CircuitBreakerTest, InheritsSwitchBehavior) {
  CircuitBreaker cb{"CB_2", 22.9, 12.5};

  EXPECT_TRUE(cb.isClosed());
  cb.open();
  EXPECT_FALSE(cb.isClosed());
}