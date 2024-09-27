execute_process(
    COMMAND ${CMAKE_COMMAND} -E echo hello
    COMMAND ${CMAKE_COMMAND} -E xxx # 不合法的参数
    RESULTS_VARIABLE res
) # 输出：
# CMake Error: cmake version 2.20
# Usage: C:/Program Files/CMake/bin/cmake.exe -E <command> [arguments...]
# ...

message("${res}") # 输出：0;1