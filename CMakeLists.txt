cmake_minimum_required(VERSION 3.12)
project(Wet1DataStructures)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG ")

add_executable(Wet1DataStructures main.cpp AVLtree.h)