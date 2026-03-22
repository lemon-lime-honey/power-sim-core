#include <gtest/gtest.h>

#include <complex>

#include "models/BaseSystem.hpp"
#include "models/Capacitor.hpp"

using namespace powersim::models;

class CapacitorTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }

  Capacitor shuntCap{"SC_Bank", 1, 154.0, 50.0};
};

TEST_F(CapacitorTest, CalculatesCapacitiveImpedanceWithNegativeSign) {
  auto z = shuntCap.getImpedance();

  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_DOUBLE_EQ(z.imag(), -4743.2);
}

TEST_F(CapacitorTest, HandlesZeroCapacity) {
  Capacitor zeroCap{"Empty_Bank", 1, 154.0, 0.0};
  auto z = zeroCap.getImpedance();

  EXPECT_DOUBLE_EQ(z.imag(), 0.0);
}

TEST_F(CapacitorTest, VerifiesShuntConnection) {
  auto buses = shuntCap.getConnectedBuses();
  EXPECT_EQ(buses.first, 1);
  EXPECT_EQ(buses.second, 0);
}