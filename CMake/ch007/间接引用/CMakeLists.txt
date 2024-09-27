cmake_minimum_required(VERSION 3.20)

project(transitive-usage-for-indirect-reference)

add_library(A STATIC "../../ch002/间接引用/liba/a.cpp")
target_include_directories(A PUBLIC "../../ch002/间接引用/liba")

add_library(B STATIC "../../ch002/间接引用/libb/b.cpp")
target_include_directories(B PUBLIC "../../ch002/间接引用/libb")
target_link_libraries(B PUBLIC A)

add_executable(main "../../ch002/间接引用/main.cpp")
target_link_libraries(main PRIVATE B)
