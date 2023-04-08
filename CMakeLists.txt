cmake_minimum_required(VERSION 3.21)
project(CPP7_MLP_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/controller)
include_directories(src/Model/ActivateFunctions)
include_directories(src/Model/Graph)
include_directories(src/Model/Matrix)
include_directories(src/Model/Network)
#include_directories(src/view)

add_executable(CPP7_MLP_1
        src/controller/controller.cc
        src/controller/controller.h
        src/Model/ActivateFunctions/ActivateFunction.cpp
        src/Model/ActivateFunctions/ActivateFunction.h
        src/Model/Graph/GraphNeuron.cpp
        src/Model/Graph/GraphNeuron.h
        src/Model/Graph/GraphPerceptron.cpp
        src/Model/Graph/GraphPerceptron.h
        src/Model/Matrix/Matrix.cpp
        src/Model/Matrix/Matrix.h
        src/Model/Network/Network.cpp
        src/Model/Network/Network.h
        src/Model/test.cc
#        src/view/main.cpp
#        src/view/render_scene.cpp
#        src/view/render_scene.h
#        src/view/view.cpp
#        src/view/view.h
        )
