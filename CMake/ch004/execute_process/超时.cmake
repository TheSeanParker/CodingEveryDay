execute_process(
    COMMAND ${CMAKE_COMMAND} -Dtext=1 -P 延时输出日志.cmake
    TIMEOUT 0.1
    RESULT_VARIABLE res
) # 输出：1

message("${res}") # 输出：Process terminated due to timeout