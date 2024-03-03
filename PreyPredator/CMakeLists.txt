cmake_minimum_required(VERSION 3.24)
project(lab_7___problem)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_7___problem
        Entity.cpp
        Entity.h
        EntityType.h
        main.cpp
        SimulationGrid.cpp
        SimulationGrid.h
        tests.cpp)
