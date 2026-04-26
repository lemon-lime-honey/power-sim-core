#include <gtest/gtest.h>

#include "models/BaseSystem.hpp"
#include "models/Capacitor.hpp"

using namespace powersim::models;

TEST(CapacitorTest, CalculatesImpedancePU) {
  BaseSystem::instance().setBase(60.0, 100.0);
  Capacitor shuntCap{"SC_Bank", 1, 154.0, 50.0};

  auto z = shuntCap.getImpedance();
  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_DOUBLE_EQ(z.imag(), -2.0);
}
