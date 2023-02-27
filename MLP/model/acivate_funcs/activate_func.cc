#include "activate_func.h"

void ActivateFunction::set() {
    std::cout << "Set activate func\n -sigmoid 1\n ReLU 2\n Th(x) 3\n ";
    int tmp;
    std::cin >> tmp;
    switch(tmp) {
        case sigmoid:
            actFunc = sigmoid;
            break;
        case ReLU:
            actFunc = ReLU;
            break;
        case thx:
            actFunc = thx;
            break;
        default:
            throw std::runtime_error("Error read actFunc");
            break;
    }
}

void ActivateFunction::use(std::vector< float > &value, int n) {
    switch (actFunc) {
        case activateFunc::sigmoid:
            for (int i = 0; i < n; i++)
                value[i] = 1 / (1 + exp(-value[i]));
            break;
        case activateFunc::ReLU:
            for (int i = 0; i < n; i++) {
                if (value[i] < 0)
                    value[i] *= 0.01;
                else if (value[i] > 1)
                    value[i] = 1. + 0.01 * (value[i] - 1.);
            }
            break;
        case activateFunc::thx:
            for (int i = 0; i < n; i++) {
                if (value[i] < 0)
                    value[i] = 0.01 * (exp(value[i]) - exp(-value[i])) / (exp(value[i]) + exp(value[i]));
                else
                    value[i] = (exp(value[i]) - exp(-value[i])) / (exp(value[i]) + exp(value[i]));
            }
            break;
        default:
            throw std::runtime_error("Error actFunc\n");
            break;
    }
}

void ActivateFunction::useDer(std::vector< float > &value, int n) {
    switch(actFunc) {
        case activateFunc::sigmoid:
            for (int i = 0; i < n; i++)
                value[i] = value[i] * (1 - value[i]);
            break;
        case activateFunc::ReLU:
            for (int i = 0; i < n; i++) {
                if (value[i] < 0 || value[i] > 1)
                    value[i] = 0.01;
                else
                    value[i] = 1;
            }
            break;
        case activateFunc::thx:
            for (int i = 0; i < n; i++) {
                if (value[i] < 0)
                    value[i] = 0.01 * (1 - value[i] * value[i]);
                else
                    value[i] = 1 - value[i] * value[i];
            }
            break;
        default:
            throw std::runtime_error("Error actFunc\n");
            break;
    }
}

