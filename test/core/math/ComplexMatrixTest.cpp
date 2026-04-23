#include <gtest/gtest.h>

#include <complex>
#include <stdexcept>

#include "core/math/ComplexMatrix.hpp"

using namespace powersim::core::math;

#define EXPECT_COMPLEX_NEAR(val, expected, tol)      \
  EXPECT_NEAR((val).real(), (expected).real(), tol); \
  EXPECT_NEAR((val).imag(), (expected).imag(), tol)

TEST(ComplexMatrixTest, InitializationAndAccess) {
  ComplexMatrix mat(2, 3);
  EXPECT_EQ(mat.getRows(), 2);
  EXPECT_EQ(mat.getCols(), 3);

  EXPECT_COMPLEX_NEAR(mat(0, 0), std::complex<double>(0.0, 0.0), 1e-9);

  mat(1, 2) = {1.5, -2.5};
  EXPECT_COMPLEX_NEAR(mat(1, 2), std::complex<double>(1.5, -2.5), 1e-9);
}

TEST(ComplexMatrixTest, InverseIdentityMatrix) {
  ComplexMatrix mat(2, 2);
  mat(0, 0) = {1.0, 0.0};
  mat(0, 1) = {0.0, 0.0};
  mat(1, 0) = {0.0, 0.0};
  mat(1, 1) = {1.0, 0.0};

  ComplexMatrix inv = mat.inverse();

  EXPECT_COMPLEX_NEAR(inv(0, 0), std::complex<double>(1.0, 0.0), 1e-9);
  EXPECT_COMPLEX_NEAR(inv(0, 1), std::complex<double>(0.0, 0.0), 1e-9);
  EXPECT_COMPLEX_NEAR(inv(1, 0), std::complex<double>(0.0, 0.0), 1e-9);
  EXPECT_COMPLEX_NEAR(inv(1, 1), std::complex<double>(1.0, 0.0), 1e-9);
}

TEST(ComplexMatrixTest, InverseRealMatrix) {
  ComplexMatrix mat(2, 2);

  mat(0, 0) = {4.0, 0.0};
  mat(0, 1) = {7.0, 0.0};
  mat(1, 0) = {2.0, 0.0};
  mat(1, 1) = {6.0, 0.0};

  ComplexMatrix inv = mat.inverse();

  EXPECT_COMPLEX_NEAR(inv(0, 0), std::complex<double>(0.6, 0.0), 1e-9);
  EXPECT_COMPLEX_NEAR(inv(0, 1), std::complex<double>(-0.7, 0.0), 1e-9);
  EXPECT_COMPLEX_NEAR(inv(1, 0), std::complex<double>(-0.2, 0.0), 1e-9);
  EXPECT_COMPLEX_NEAR(inv(1, 1), std::complex<double>(0.4, 0.0), 1e-9);
}

TEST(ComplexMatrixTest, InverseComplexMatrix) {
  ComplexMatrix mat(2, 2);
  mat(0, 0) = {1.0, 1.0};
  mat(0, 1) = {0.0, 0.0};
  mat(1, 0) = {0.0, 0.0};
  mat(1, 1) = {0.0, -2.0};

  ComplexMatrix inv = mat.inverse();

  EXPECT_COMPLEX_NEAR(inv(0, 0), std::complex<double>(0.5, -0.5), 1e-9);
  EXPECT_COMPLEX_NEAR(inv(1, 1), std::complex<double>(0.0, 0.5), 1e-9);
}

TEST(ComplexMatrixTest, InverseThrowsOnSingularMatrix) {
  ComplexMatrix mat(2, 2);
  mat(0, 0) = {1.0, 0.0};
  mat(0, 1) = {2.0, 0.0};
  mat(1, 0) = {2.0, 0.0};
  mat(1, 1) = {4.0, 0.0};

  EXPECT_THROW(mat.inverse(), std::runtime_error);
}

TEST(ComplexMatrixTest, InverseThrowsOnNonSquareMatrix) {
  ComplexMatrix mat(2, 3);
  EXPECT_THROW(mat.inverse(), std::logic_error);
}