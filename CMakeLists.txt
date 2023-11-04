cmake_minimum_required(VERSION 3.27.7)
project(Lab1 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab1 src/main.cpp src/vector.cpp include/vector.hpp)

target_include_directories(Lab1 PUBLIC include)

find_package(OpenMP REQUIRED)
target_link_libraries(Lab1 PUBLIC OpenMP::OpenMP_CXX)
