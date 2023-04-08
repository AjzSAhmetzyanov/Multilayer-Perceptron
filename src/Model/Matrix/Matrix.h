//
// Created by Luigi Ketter on 3/11/23.
//

#ifndef CPP7_MLP_1_MATRIX_MATRIX_H
#define CPP7_MLP_1_MATRIX_MATRIX_H

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

namespace s21 {
class Matrix final {
 private:
  std::vector<std::vector<double>> matrix;

  int row{}, col{};

  std::mt19937 random_generator_;

 public:
  Matrix() = default;

  ~Matrix() = default;

  void init(int &, int &);

  void rand_();

  static void multi(const Matrix &, const std::vector<double> &, int,
                    std::vector<double> &);

  static void multi_t(const Matrix &, const std::vector<double> &, int,
                      std::vector<double> &);

  double &operator()(int, int);

  friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    for (int i = 0; i < m.row; ++i) {
      for (int j = 0; j < m.col; j++) {
        os << m.matrix[i][j] << " ";
      }
    }
    return os;
  }

  friend std::istream &operator>>(std::istream &is, Matrix &m) {
    for (int i = 0; i < m.row; ++i) {
      for (int j = 0; j < m.col; j++) {
        is >> m.matrix[i][j];
      }
    }
    return is;
  }
};
}  // namespace s21

#endif  // CPP7_MLP_1_MATRIX_MATRIX_H
