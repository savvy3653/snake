cmake_minimum_required(VERSION 3.31)

project(untitled9)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled9 main.cpp)

target_link_options(untitled9 PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
)