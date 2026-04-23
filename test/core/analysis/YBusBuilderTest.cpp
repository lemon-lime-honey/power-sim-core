#include <gtest/gtest.h>

#include <complex>

#include "core/analysis/YBusBuilder.hpp"
#include "models/PowerSystem.hpp"

using namespace powersim::models;
using namespace powersim::core::analysis;

class YBusBuilderTest : public ::testing::Test {
 protected:
  PowerSystem sys;

  void SetUp() override {
    BaseSystem::instance().setBase(60.0, 100.0);

    sys.addBus(std::make_shared<Bus>(1, "Bus1", 22.9));
    sys.addBus(std::make_shared<Bus>(2, "Bus2", 22.9));
  }
};

TEST_F(YBusBuilderTest, BuildsCorrectYBusForSimpleSystem) {
  auto source = std::make_shared<PowerSource>("Source", 22.9, 1000.0);
  sys.addPowerSource(source, 1);

  auto line = std::make_shared<Line>("Line1", 1, 2, 0.05,
                                     0.1 / (2 * 3.14159 * 60), 0.0, 0.0);
  sys.addLine(line);

  auto ybus = YBusBuilder::build(sys);

  ASSERT_EQ(ybus.getRows(), 2);

  std::complex<double> y_source = 1.0 / source->getImpedance();
  std::complex<double> y_line = 1.0 / line->getImpedance();

  std::complex<double> expected_y11 = y_source + y_line;
  std::complex<double> expected_y12 = -y_line;
  std::complex<double> expected_y22 = y_line;

  EXPECT_NEAR(ybus(0, 0).real(), expected_y11.real(), 1e-5);
  EXPECT_NEAR(ybus(0, 0).imag(), expected_y11.imag(), 1e-5);

  EXPECT_NEAR(ybus(0, 1).real(), expected_y12.real(), 1e-5);
  EXPECT_NEAR(ybus(0, 1).imag(), expected_y12.imag(), 1e-5);

  EXPECT_NEAR(ybus(1, 1).real(), expected_y22.real(), 1e-5);
  EXPECT_NEAR(ybus(1, 1).imag(), expected_y22.imag(), 1e-5);
}