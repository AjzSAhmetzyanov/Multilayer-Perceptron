#include "controller.h"
using namespace s21;
Controller::~Controller() { delete netw; }

std::pair<double, double> Controller::start_training(std::string &train_file,
                                                     std::string &save_file,
                                                     const double &lr,
                                                     const int &epoch,
                                                     const int &L) {
  return netw->start_training(train_file, save_file, lr, epoch, L);
}

std::pair<double, double> Controller::start_testing(std::string &test_file,
                                                    std::string &save_file,
                                                    const int &L) {
  return netw->start_testing(test_file, save_file, L);
}

int Controller::ready_weigth(const std::vector<double> &vec) {
  return netw->ready_weights(vec);
}

std::pair<double, double> Controller::cross_val(const int &L, std::string &file,
                                                const int &k, const int &epoch,
                                                const double &lr) {
  return netw->cross_validation(L, file, k, epoch, lr);
}
