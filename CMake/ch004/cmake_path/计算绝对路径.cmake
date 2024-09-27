set(path example.txt)
cmake_path(ABSOLUTE_PATH path OUTPUT_VARIABLE res)
message("${res}") # 输出：C:/CMake-Book/src/ch004/cmake_path/example.txt