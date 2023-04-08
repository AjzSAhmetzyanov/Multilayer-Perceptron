//
// Created by Luigi Ketter on 3/11/23.
//

#ifndef CPP7_MLP_1_ACTIVATEFUNCTION_H
#define CPP7_MLP_1_ACTIVATEFUNCTION_H

#include <cmath>
#include <iostream>
#include <vector>

namespace s21 {

enum activateFunc { sigmoid = 1, ReLU = 2, thx = 3 };

class ActivateFunction final {
 private:
  activateFunc actFunc;

 public:
  ActivateFunction() = default;

  ~ActivateFunction() = default;

  void set();

  void use(std::vector<double> &, int &);

  double useDer(double &);
};

}  // namespace s21

#endif  // CPP7_MLP_1_ACTIVATEFUNCTION_H
