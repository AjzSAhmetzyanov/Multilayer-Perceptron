//
// Created by Luigi Ketter on 3/22/23.
//

#ifndef CPP7_MLP_1_GRAPHPERCEPTRON_H
#define CPP7_MLP_1_GRAPHPERCEPTRON_H
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iterator>
#include <random>
#include <sstream>
#include <vector>
#include <chrono>

#include "../ActivateFunctions/ActivateFunction.h"
#include "GraphNeuron.h"

namespace s21 {
class GraphPerceptron final {
 private:
  int L{}, step{};

  std::vector<double> MSE_;

  std::vector<int> size;

  ActivateFunction actFunc{};

  std::vector<GraphNeuron> weights;

  std::vector<std::vector<double>> neurons_val;

  std::vector<std::vector<double>> delta;

 public:
  GraphPerceptron() = default;

  ~GraphPerceptron() = default;

  void init(int);

  void print_config();

  void set_input(std::vector<double> &);

  void training_(std::string &, double &, int &);

  void testing_(std::string &, std::string &);

  int forward_feed();

  void error_test(int &);

  double MSE(int &);

  void print_values(int &);

  void back_propogation(double &);

  void weights_updater(double &);

  void save_weights(std::string &);

  void read_weights(std::string &);

  std::pair<double, double> cross_validation(const int &L,
                                                                std::string &file,
                                                                const int &k,
                                                                const int &epoch,
                                                                const double &lr);
    static std::pair<std::vector<std::vector<std::string>>,
            std::vector<std::vector<std::string>>>
    split_data(const std::vector<std::vector<std::string>> &data, double fraction,
               bool shuffle = true);

  static std::vector<std::vector<std::string>> read_file(std::string &);

  static int search_max_index(std::vector<double> &);
};
}  // namespace s21

#endif  // CPP7_MLP_1_GRAPHPERCEPTRON_H
