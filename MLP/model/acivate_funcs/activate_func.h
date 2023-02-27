#pragma once
#include <iostream>
#include <cmath>
#include <vector>
enum activateFunc {sigmoid = 1, ReLU = 2, thx = 3};

class ActivateFunction{
public:
    activateFunc actFunc;
public:
    void set();
    void use(std::vector< float > &value, int n);
    void useDer(std::vector< float > &value, int n);
};