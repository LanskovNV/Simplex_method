cmake_minimum_required(VERSION 3.13)
project(Simplex_method)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp
        IndexSet.cpp
        IndexSet.h
        Matrix.cpp
        Matrix.h
        SimplexSolver.cpp
        SimplexSolver.h
        Vec.cpp
        Vec.h)
