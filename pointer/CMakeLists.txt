
cmake_minimum_required(VERSION 2.8.3)
project(lio_sam)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "-O1  ")
set(CMAKE_CXX_FLAGS "-Wall ")
set(CMAKE_CXX_FLAGS "-fsanitize=pthread ")
set(CMAKE_CXX_FLAGS "-fsanitize=address -g ")
# set(CMAKE_CXX_FLAGS "-fsanitize=leak -g")
# set(CMAKE_CXX_FLAGS "-fsanitize=undefined -g")
# set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer")
add_executable(pointer pointer.cpp)