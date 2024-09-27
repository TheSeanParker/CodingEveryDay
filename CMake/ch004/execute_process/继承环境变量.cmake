set(ENV{text} hello)
execute_process(COMMAND ${CMAKE_COMMAND} -P 输出环境变量.cmake)
# 输出：hello

set(ENV{text} world)
execute_process(COMMAND ${CMAKE_COMMAND} -P 输出环境变量.cmake COMMAND_ECHO STDERR)
# 输出：world