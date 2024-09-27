cmake_minimum_required(VERSION 3.20)

project(file_generate)

add_library(lib lib.cpp)

file(GENERATE OUTPUT out-$<CONFIG>.txt
     CONTENT $<TARGET_FILE:lib>
     TARGET lib
)