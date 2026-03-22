#include <gtest/gtest.h>

#include <complex>

#include "models/BaseSystem.hpp"
#include "models/Reactor.hpp"

using namespace powersim::models;

class ReactorTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }

  Reactor shuntReactor{"Shunt_Ref", 1, 154.0, 100.0};

  Reactor seriesReactor{"Series_Limiter", 2, 3, 22.9, 5.0};
};

TEST_F(ReactorTest, CalculatesShuntImpedanceCorrectly) {
  auto z = shuntReactor.getImpedance();

  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_DOUBLE_EQ(z.imag(), 2371.6);
}

TEST_F(ReactorTest, CalculatesSeriesImpedanceCorrectly) {
  auto z = seriesReactor.getImpedance();

  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_NEAR(z.imag(), 1048.82, 1e-9);
}

TEST_F(ReactorTest, VerifiesTopology) {
  auto shuntBuses = shuntReactor.getConnectedBuses();
  EXPECT_EQ(shuntBuses.first, 1);
  EXPECT_EQ(shuntBuses.second, 0);

  auto seriesBuses = seriesReactor.getConnectedBuses();
  EXPECT_EQ(seriesBuses.first, 2);
  EXPECT_EQ(seriesBuses.second, 3);
}