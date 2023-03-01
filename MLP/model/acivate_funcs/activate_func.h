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
        static float use(float, int);
        static float useDer(float, int);
    };

} // namespace s21
