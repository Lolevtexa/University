cmake_minimum_required(VERSION 3.10)
project(Interference LANGUAGES CXX)

# Используем C++17 и компилятор clang
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

# Пути к заголовкам
include_directories(${PROJECT_SOURCE_DIR}/include)

# Все .cpp в src/ — в единый исполняемый файл
file(GLOB SOURCES src/*.cpp)
add_executable(interference ${SOURCES})
