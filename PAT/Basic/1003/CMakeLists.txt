cmake_minimum_required(VERSION 3.3)
project(1003)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    1003/Source.cpp
    1003/test.in
    1003/test.out)

add_executable(1003 ${SOURCE_FILES})