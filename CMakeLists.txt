cmake_minimum_required(VERSION 3.22)

project(matrix-handler CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(run_tests src/matrix.cpp src/matrix_multithread_handler.cpp src/test.cpp)
add_executable(measure_time src/matrix.cpp src/matrix_multithread_handler.cpp src/time_measuring.cpp)
