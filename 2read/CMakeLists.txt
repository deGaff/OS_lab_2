cmake_minimum_required(VERSION 3.20)
project(2read)

set(CMAKE_CXX_STANDARD 14)

add_executable(2read main.cpp menu.cpp menu.h safe_input.h safe_input.cpp projRead.cpp projRead.h)
