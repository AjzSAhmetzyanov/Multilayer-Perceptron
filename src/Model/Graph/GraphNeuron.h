//
// Created by Luigi Ketter on 3/22/23.
//

#ifndef CPP7_MLP_1_GRAPHNEURON_H
#define CPP7_MLP_1_GRAPHNEURON_H
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

namespace s21 {
class GraphNeuron final {
 private:
  std::vector<std::vector<double>> matrix;

  int row{}, col{};

  std::mt19937 random_generator_;

 public:
  GraphNeuron() = default;

  ~GraphNeuron() = default;

  void init(int &, int &);

  void rand_();

  static void multi(const GraphNeuron &, const std::vector<double> &, int,
                    std::vector<double> &);

  static void multi_t(const GraphNeuron &, const std::vector<double> &, int,
                      std::vector<double> &);

  double &operator()(int, int);

  friend std::ostream &operator<<(std::ostream &os, const GraphNeuron &m) {
    for (int i = 0; i < m.row; ++i) {
      for (int j = 0; j < m.col; j++) {
        os << m.matrix[i][j] << " ";
      }
    }
    return os;
  }

  friend std::istream &operator>>(std::istream &is, GraphNeuron &m) {
    for (int i = 0; i < m.row; ++i) {
      for (int j = 0; j < m.col; j++) {
        is >> m.matrix[i][j];
      }
    }
    return is;
  }
};
}  // namespace s21

#endif  // CPP7_MLP_1_GRAPHNEURON_H
