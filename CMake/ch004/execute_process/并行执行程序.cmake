execute_process(
    COMMAND ${CMAKE_COMMAND} -Dtext=1 -P 延时输出日志.cmake
    COMMAND ${CMAKE_COMMAND} -Dtext=2 -P 延时输出日志.cmake
    COMMAND ${CMAKE_COMMAND} -Dtext=3 -P 延时输出日志.cmake
)