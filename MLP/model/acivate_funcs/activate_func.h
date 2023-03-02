#pragma once
#include <iostream>
#include <cmath>
#include <vector>

namespace s21
{
    enum activateFunc {sigmoid = 1, ReLU = 2, thx = 3};

    class ActivateFunction{
    public:
        static activateFunc actFunc;
        static void set();
        static double use(double, int);
        static double useDer(double, int);
    };

} // namespace s21
