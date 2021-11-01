cmake_minimum_required(VERSION 3.20)
project(2)

set(CMAKE_CXX_STANDARD 17)

add_executable(2 main.cpp menu.cpp menu.h safe_input.cpp safe_input.h getsysinfo.h menu.h getsysinfo.cpp mem_manager.cpp mem_manager.h)
