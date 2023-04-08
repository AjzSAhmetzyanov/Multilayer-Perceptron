//
// Created by Luigi Ketter on 3/22/23.
//

#include "GraphNeuron.h"

using namespace s21;

void GraphNeuron::init(int &row_, int &col_) {
  this->row = row_;
  this->col = col_;
  matrix.resize(row);
  for (int i = 0; i < row; i++) matrix[i].resize(col);

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i][j] = 0;
    }
  }
}
void GraphNeuron::rand_() {
  std::random_device rd_;
  std::mt19937 temp(rd_());
  random_generator_ = temp;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matrix[i][j] = ((int)random_generator_() % 10000) * 0.0001;
    }
  }
}
void GraphNeuron::multi(const GraphNeuron &m1,
                        const std::vector<double> &neuron, int n,
                        std::vector<double> &c) {
  if (m1.col != n) throw std::runtime_error("Error Multi \n");

  for (int i = 0; i < m1.row; ++i) {
    double tmp = 0;
    for (int j = 0; j < m1.col; ++j) {
      tmp += m1.matrix[i][j] * neuron[j];
    }
    c[i] = tmp;
  }
}
void GraphNeuron::multi_t(const GraphNeuron &m1,
                          const std::vector<double> &neuron, int n,
                          std::vector<double> &c) {
  if (m1.row != n) throw std::runtime_error("Error Multi_T \n");

  for (int i = 0; i < m1.col; ++i) {
    double tmp = 0;
    for (int j = 0; j < m1.row; ++j) {
      tmp += m1.matrix[j][i] * neuron[j];
    }
    c[i] = tmp;
  }
}
double &GraphNeuron::operator()(int i, int j) { return matrix[i][j]; }
