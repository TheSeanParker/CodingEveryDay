cmake_minimum_required(VERSION 3.20)
project(check-include-files)
include(CheckIncludeFiles)

set(CMAKE_REQUIRED_INCLUDES "${CMAKE_SOURCE_DIR}")
check_include_files("stdio.h;a.h" res) # 输出：
# -- Looking for include file stdio.h, a.h
# -- Looking for include file stdio.h, a.h - found