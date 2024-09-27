message("${CMAKE_CURRENT_LIST_FILE}")
# 输出：C:/CMake-Book/src/ch004/cmake_path/计算相对路径.cmake

cmake_path(RELATIVE_PATH CMAKE_CURRENT_LIST_FILE OUTPUT_VARIABLE res)
message("${res}") # 输出：计算相对路径.cmake