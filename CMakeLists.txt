cmake_minimum_required(VERSION 3.21)
project(Multilayer_Perceptron)

set(CMAKE_CXX_STANDARD 14)

include_directories(MLP/controller)
include_directories(MLP/model/acivate_funcs)
include_directories(MLP/model/matrix_network)
include_directories(MLP/view)

add_executable(Multilayer_Perceptron
        MLP/emnist-letters/emnist-letters-mapping.txt
        MLP/emnist-letters/emnist-letters-test.csv
        MLP/emnist-letters/emnist-letters-train.csv
        MLP/model/acivate_funcs/activate_func.cc
        MLP/model/acivate_funcs/activate_func.h
        MLP/model/matrix_network/matrix_network.cpp
        MLP/model/matrix_network/matrix_network.h
        MLP/test.cc)
