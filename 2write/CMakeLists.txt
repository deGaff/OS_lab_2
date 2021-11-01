cmake_minimum_required(VERSION 3.20)
project(2write)

set(CMAKE_CXX_STANDARD 14)

add_executable(2write main.cpp menu.cpp menu.h safe_input.h safe_input.cpp projWrite.cpp projWrite.h)
