message("${CMAKE_CURRENT_LIST_FILE}")
# 输出：C:/CMake-Book/src/ch004/file/计算相对路径.cmake

file(RELATIVE_PATH res ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_LIST_FILE})
message("${res}") # 输出：计算相对路径.cmake