execute_process(
    COMMAND ${CMAKE_COMMAND} -E echo hello
    COMMAND ${CMAKE_COMMAND} -E echo world
    OUTPUT_VARIABLE out
    ECHO_OUTPUT_VARIABLE
) # 输出：world

message("${out}") # 输出：world

execute_process(
    COMMAND ${CMAKE_COMMAND} -Dtext=hello -P 输出变量.cmake
    COMMAND ${CMAKE_COMMAND} -Dtext=world -P 输出变量.cmake
    ERROR_VARIABLE out
    ECHO_ERROR_VARIABLE
) # 输出：
# world
# hello

message("${out}") 
# 输出：
# world
# hello