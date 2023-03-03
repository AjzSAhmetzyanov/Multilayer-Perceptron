#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "model/matrix_network/matrix_network.h"

int main(){
    std::string fname = "emnist-letters/emnist-letters-train.csv";
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line, word;
    std::fstream file (fname, std::ios::in);
    if(file.is_open()) {
        while(getline(file, line)) {
            row.clear();
            std::stringstream str(line);
            while(getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    } else
        std::cout<<"Could not open the file\n";

    std::vector<double> train_1 = {};
    for(int j=1;j<content[0].size();j++) {
        train_1.push_back(stod(content[0][j])/255);
    }
//    for(auto i : train_1) {
//        std::cout<<i<<std::endl;
//    }
    s21::MatrixNetwork matr(4, train_1);
    matr.MultiplyWeights(matr.getSLayer(), 0);
    matr.MultiplyWeights(matr.getALayers()[0], 1);
    matr.MultiplyWeights(matr.getALayers()[1], 2);
    matr.MultiplyWeights(matr.getALayers()[2], 3);
//    matr.MultiplyWeights(matr.getALayers()[3], 4);
//    matr.MultiplyWeights(matr.getALayers()[4], 5);

    auto weights = matr.getWeights();
    while (matr.solve_errors(stoi(content[0][0]))[22] != 23) {
        matr.ComputeDelta(stoi(content[0][0]));
//    std::cout << std::endl;
        matr.MultiplyWeights(matr.getSLayer(), 0);
        matr.MultiplyWeights(matr.getALayers()[0], 1);
        matr.MultiplyWeights(matr.getALayers()[1], 2);
        matr.MultiplyWeights(matr.getALayers()[2], 3);
    }

    matr.solve_errors(stoi(content[0][0]));
    std::cout << std::endl;
//    matr.MultiplyWeights(matr.getSLayer(), 0);
//    matr.MultiplyWeights(matr.getALayers()[0], 1);
//    matr.MultiplyWeights(matr.getALayers()[1], 2);
//    matr.MultiplyWeights(matr.getALayers()[2], 3);
//
//    matr.solve_errors(stoi(content[0][0]));
//    std::cout << std::endl;

    std::cout << stoi(content[0][0]);
    return 0;
}

