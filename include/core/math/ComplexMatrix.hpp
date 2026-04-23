#pragma once

#include <cmath>
#include <complex>
#include <stdexcept>
#include <vector>

namespace powersim::core::math {
class ComplexMatrix {
 public:
  ComplexMatrix(size_t rows, size_t cols)
      : rows_(rows),
        cols_(cols),
        data_(rows, std::vector<std::complex<double>>(cols, {0.0, 0.0})) {}

  size_t getRows() const { return rows_; }
  size_t getCols() const { return cols_; }

  std::complex<double>& operator()(size_t r, size_t c) { return data_[r][c]; }
  const std::complex<double>& operator()(size_t r, size_t c) const {
    return data_[r][c];
  }

  ComplexMatrix inverse() const {
    if (rows_ != cols_) {
      throw std::logic_error("Matrix must be square to find an inverse.");
    }

    size_t n = rows_;
    ComplexMatrix augmented(n, 2 * n);

    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        augmented(i, j) = data_[i][j];
      }
      augmented(i, i + n) = {1.0, 0.0};
    }

    for (size_t i = 0; i < n; ++i) {
      size_t maxRow = i;
      double maxVal = std::abs(augmented(i, i));
      for (size_t k = i + 1; k < n; ++k) {
        if (std::abs(augmented(k, i)) > maxVal) {
          maxVal = std::abs(augmented(k, i));
          maxRow = k;
        }
      }

      if (maxVal < 1e-12) {
        throw std::runtime_error(
            "Matrix is singular or nearly singular. Cannot invert.");
      }

      if (maxRow != i) {
        std::swap(augmented.data_[i], augmented.data_[maxRow]);
      }

      std::complex<double> pivot = augmented(i, i);
      for (size_t j = 0; j < 2 * n; ++j) {
        augmented(i, j) /= pivot;
      }

      for (size_t k = 0; k < n; ++k) {
        if (k == i) continue;
        std::complex<double> factor = augmented(k, i);
        for (size_t j = 0; j < 2 * n; ++j) {
          augmented(k, j) -= factor * augmented(i, j);
        }
      }
    }

    ComplexMatrix result(n, n);
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < n; ++j) {
        result(i, j) = augmented(i, j + n);
      }
    }

    return result;
  }

 private:
  size_t rows_;
  size_t cols_;
  std::vector<std::vector<std::complex<double>>> data_;
};
}  // namespace powersim::core::math