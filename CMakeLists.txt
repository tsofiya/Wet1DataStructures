cmake_minimum_required(VERSION 3.9)
project(Wet1DataStructures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -DNDEBUG")

add_executable(Wet1DataStructures main.cpp AVLtree.h Schedule.h library.cpp BiDirectionalList.h main.cpp)