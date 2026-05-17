#include <gtest/gtest.h>

#include <complex>

#include "models/BaseSystem.hpp"
#include "models/Transformer.hpp"

using namespace powersim::models;

class TransformerTest : public ::testing::Test {
 protected:
  void SetUp() override { BaseSystem::instance().setBase(60.0, 100.0); }
  Transformer stepDownTx{"MTR_01",
                         1,
                         2,
                         60.0,
                         154.0,
                         22.9,
                         std::complex<double>{0.0, 0.1},
                         std::complex<double>{0.0, 0.1}};
};

TEST_F(TransformerTest, CalculatesImpedancePU) {
  auto z = stepDownTx.getImpedance();
  EXPECT_DOUBLE_EQ(z.real(), 0.0);
  EXPECT_NEAR(z.imag(), (10.0 / 100.0) * (100.0 / 60.0), 1e-9);
}