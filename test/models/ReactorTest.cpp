#include <gtest/gtest.h>

#include "models/BaseSystem.hpp"
#include "models/Reactor.hpp"

using namespace powersim::models;

TEST(ReactorTest, CalculatesImpedancePU) {
  BaseSystem::instance().setBase(60.0, 100.0);
  Reactor seriesReactor{"Series_Limiter", 2, 3, 22.9, 5.0};

  auto z = seriesReactor.getImpedance();
  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_DOUBLE_EQ(z.imag(), 20.0);
}