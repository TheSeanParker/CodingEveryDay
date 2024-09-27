cmake_minimum_required(VERSION 3.20)
project(push-check-state)
include(CMakePushCheckState)

include(CheckIncludeFiles)

set(CMAKE_REQUIRED_INCLUDES "${CMAKE_SOURCE_DIR}")
check_include_files("a.h" res) # 输出：
# -- Looking for include file a.h
# -- Looking for include file a.h - found

cmake_push_check_state()

set(CMAKE_REQUIRED_INCLUDES "${CMAKE_SOURCE_DIR}/b")
check_include_files("b.h" res2) # 输出：
# -- Looking for include file b.h
# -- Looking for include file b.h - found

cmake_pop_check_state()

set(CMAKE_REQUIRED_INCLUDES "${CMAKE_SOURCE_DIR}")
check_include_files("a.h" res3) # 输出：
# -- Looking for include file a.h
# -- Looking for include file a.h - found