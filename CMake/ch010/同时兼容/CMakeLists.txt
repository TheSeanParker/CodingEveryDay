cmake_minimum_required(VERSION 3.19)

project(if-policy)

if(POLICY CMP0115)
    # 支持策略CMP0115，肯定是CMake 3.20及以上版本
    cmake_policy(SET CMP0115 NEW)
    add_executable(A main.cpp) # 必须显式指定扩展名
else()
    # 仍是CMake 3.19
    add_executable(A main) # 仍可使用省略扩展名的写法
endif()