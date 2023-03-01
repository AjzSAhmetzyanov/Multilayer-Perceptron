#include "activate_func.h"

namespace s21
{
    
    // void ActivateFunction::set() {
    //     std::cout << "Set activate func\n -sigmoid 1\n ReLU 2\n Th(x) 3\n ";
    //     int tmp;
    //     std::cin >> tmp;
    //     switch(tmp) {
    //         case sigmoid:
    //             actFunc = sigmoid;
    //             break;
    //         case ReLU:
    //             actFunc = ReLU;
    //             break;
    //         case thx:
    //             actFunc = thx;
    //             break;
    //         default:
    //             throw std::runtime_error("Error read actFunc");
    //             break;
    //     }
    // }

    float ActivateFunction::use(float x, int num) {
        switch (num) {
            case activateFunc::sigmoid:
                // for (int i = 0; i < n; i++)
                    x = 1 / (1 + exp(-x));
                break;
            case activateFunc::ReLU:
                // for (int i = 0; i < n; i++) {
                    if (x < 0)
                        x *= 0.01;
                    else if (x > 1)
                        x = 1. + 0.01 * (x - 1.);
                // }
                break;
            case activateFunc::thx:
                // for (int i = 0; i < n; i++) {
                    if (x < 0)
                        x = 0.01 * (exp(x) - exp(-x)) / (exp(x) + exp(x));
                    else
                        x = (exp(x) - exp(-x)) / (exp(x) + exp(x));
                // }
                break;
            default:
                throw std::runtime_error("Error actFunc\n");
                break;
        }
        return x;
    }

     float ActivateFunction::useDer(float x, int num) {
         switch(num) {
             case activateFunc::sigmoid:
                 x = x * (1 - x);
                 break;
             case activateFunc::ReLU:
                 if (x < 0 || x > 1)
                     x = 0.01;
                 else
                     x = 1;
                 break;
             case activateFunc::thx:
                 if (x < 0)
                     x = 0.01 * (1 - x * x);
                 else
                     x = 1 - x * x;
                 break;
             default:
                 throw std::runtime_error("Error actFunc\n");
                 break;
         }
         return x;
     }

} // namespace s21
