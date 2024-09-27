# 本例程的样例输出基于MSVC编译器
cmake_minimum_required(VERSION 3.20)
project(check-compiler-flag)
include(CheckCompilerFlag)

check_compiler_flag(CXX --std=c++17 res)
# 输出：
# -- Performing Test res
# -- Performing Test res - Failed
message("${res}") # 输出空值

check_compiler_flag(CXX /std:c++17 res2)
# 输出：
# -- Performing Test res2
# -- Performing Test res2 - Success
message("${res2}") # 输出1