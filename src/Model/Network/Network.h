//
// Created by Luigi Ketter on 3/11/23.
//

#ifndef CPP7_MLP_1_NETWORK_H
#define CPP7_MLP_1_NETWORK_H
#include <algorithm>
#include <fstream>
#include <iterator>
#include <random>
#include <sstream>
#include <vector>
#include <chrono>

#include "../ActivateFunctions/ActivateFunction.h"
#include "../Matrix/Matrix.h"

namespace s21 {
class NetWork final {
 private:
  int L{}, step{};

  std::vector<double> MSE_;

  std::vector<int> size;

  ActivateFunction actFunc{};

  std::vector<Matrix> weights;

  std::vector<std::vector<double>> neurons_val;

  std::vector<std::vector<double>> delta;

 public:
  NetWork() = default;

  ~NetWork() = default;

  void init(int);

  void print_config();

  void set_input(const std::vector<double> &);

  std::pair<double, double> training_(std::string &, const double &,
                                      const int &);

  std::pair<double, double> testing_(std::string &);

  static std::pair<double, double> start_training(std::string &, std::string &,
                                                  const double &, const int &,
                                                  const int &);

  static std::pair<double, double> start_testing(std::string &, std::string &,
                                                 const int &);

  static int ready_weights(const std::vector<double> &);

  int forward_feed();

  void error_test(int &);

  double MSE(int &);

  void print_values(int &);

  void back_propogation(double &);

  void weights_updater(const double &);

  void save_weights(std::string &);

  void read_weights(std::string &);

  std::pair<double, double> cross_validation(const int &, std::string &,
                                             const int &, const int &,
                                             const double &);

  static std::pair<std::vector<std::vector<std::string>>,
                   std::vector<std::vector<std::string>>>
  split_data(const std::vector<std::vector<std::string>> &data, double fraction,
             bool shuffle = true);

  static std::vector<std::vector<std::string>> read_file(std::string &);

  static int search_max_index(std::vector<double> &);
};
}  // namespace s21

#endif  // CPP7_MLP_1_NETWORK_H
