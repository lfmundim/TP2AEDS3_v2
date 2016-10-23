cmake_minimum_required(VERSION 3.6)
project(TP2_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c vinicius.c vinicius.h map.h map.c graph.h graph.c dijkstra.h dijkstra.c)
add_executable(TP2_2 ${SOURCE_FILES})