cmake_minimum_required(VERSION 3.14)
project(MyProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g -O0")
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")
set(CMAKE_CXX_FLAGS "-m64")

# Указываем Clang как компилятор
if(NOT CMAKE_CXX_COMPILER)
    set(CMAKE_C_COMPILER "D:/Tools/mingw/bin/clang.exe")
    set(CMAKE_CXX_COMPILER "D:/Tools/mingw/bin/clang++.exe")
endif()

# Включаем директорию с заголовочными файлами
include_directories(include)

# Ищем все .cpp файлы рекурсивно
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Добавляем исполняемый файл
add_executable(my_project ${SOURCES})

# Настройки предупреждений
target_compile_options(my_project PRIVATE -Wall -Wextra -Wpedantic)
