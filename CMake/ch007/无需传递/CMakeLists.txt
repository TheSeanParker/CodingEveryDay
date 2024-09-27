cmake_minimum_required(VERSION 3.20)

project(no-transition)

add_library(A STATIC "../../ch002/无需传递/liba/a.cpp")
target_include_directories(A PUBLIC "../../ch002/无需传递/liba")

add_library(B STATIC "../../ch002/无需传递/libb/b.cpp")
target_include_directories(B PUBLIC "../../ch002/无需传递/libb")
target_link_libraries(B PRIVATE A)

add_executable(main "../../ch002/无需传递/main.cpp")
target_link_libraries(main PRIVATE B)
