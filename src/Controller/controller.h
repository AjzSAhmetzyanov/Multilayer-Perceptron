#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>

#include "../Model/Network/Network.h"
namespace s21 {
class Controller {
 private:
  s21::NetWork *netw = new s21::NetWork;

 public:
  Controller() = default;
  ~Controller();

  std::pair<double, double> start_training(std::string &, std::string &,
                                           const double &, const int &,
                                           const int &);

  std::pair<double, double> start_testing(std::string &, std::string &,
                                          const int &);

  int ready_weigth(const std::vector<double> &);

  std::pair<double, double> cross_val(const int &, std::string &, const int &,
                                      const int &, const double &);
};
}  // namespace s21
#endif  // CONTROLLER_H
