cmake_minimum_required(VERSION 3.10)

# Принудительно ставим компиляторы clang/clang++
set(CMAKE_C_COMPILER   "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(PotentialField LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O3")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(solver
    src/main.cpp
    src/Electrodes.cpp
    src/PotentialSolver.cpp
    src/FieldLine.cpp
    src/Utils.cpp
)
