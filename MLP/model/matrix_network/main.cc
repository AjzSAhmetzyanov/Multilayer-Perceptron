#include "matrix_network.h"

int main() {
    s21::MatrixNetwork matr(6);

    matr.MultiplyWeights(matr.getSLayer(), 0);
    matr.MultiplyWeights(matr.getALayers()[0], 1);
    matr.MultiplyWeights(matr.getALayers()[1], 2);
    matr.MultiplyWeights(matr.getALayers()[2], 3);
    matr.MultiplyWeights(matr.getALayers()[3], 4);
    matr.MultiplyWeights(matr.getALayers()[4], 5);
}

