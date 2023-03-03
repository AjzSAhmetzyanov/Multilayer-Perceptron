cmake_minimum_required(VERSION 3.21)
project(MLP)

include_directories(controller)
include_directories(model/acivate_funcs)
include_directories(model/matrix_network)
include_directories(view)

set(CMAKE_CXX_STANDARD 17)

add_executable(MLP main.cpp
        model/acivate_funcs/activate_func.cc
        model/acivate_funcs/activate_func.h
        model/matrix_network/matrix_network.cpp
        model/matrix_network/matrix_network.h
        test.cc)


