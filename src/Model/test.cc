#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "Graph/GraphPerceptron.h"
#include "Network/Network.h"

int main() {
  // train
  std::string train_file =
      "../datasets/emnist-letters/emnist-letters-train.csv";
  std::string test_file = "../datasets/emnist-letters/emnist-letters-test.csv";
  std::string file = "/Users/luigiket/CPP7_MLP-1/src/Model/Graph/1.txt";
  int epoch = 5;
  double lr = 0.08;
  //    s21::GraphPerceptron graph;
  //    graph.init(3);
  //    graph.training_(train_file, lr, epoch);
  //    graph.testing_(test_file,file);
  s21::NetWork netw;
  netw.init(3);
  netw.training_(train_file, lr, epoch);
  netw.testing_(test_file, file);
  return 0;
}
