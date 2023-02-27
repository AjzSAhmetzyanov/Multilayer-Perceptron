#include "model/acivate_funcs/activate_func.h"
#include <vector>

int main() {
    std::vector<float> vv {1.2, 1.3, 1.4, 1.5};
//    std::vector<float> vv1 {1.2, 1.3, 1.4, 1.5};
//    std::vector<float> vv2 {};
//    ActivateFunction act;
//    act.set();
//    act.useDer(vv, vv.size());
//    for (int i = 0; i < vv.size(); i++) {
//        for (int j = 0; j < vv1.size(); j++) {
//            vv2.push_back(vv[i]*vv1[j]);
//        }
//    }
    for (auto i : vv)
        std::cout << i << std::endl;
    return 0;
}