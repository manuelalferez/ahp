cmake_minimum_required(VERSION 3.16)
project(ahp)

set(CMAKE_CXX_STANDARD 20)

add_executable(ahp src/main.cpp src/Loader.cpp src/Loader.h src/Ahp.cpp src/Ahp.h)