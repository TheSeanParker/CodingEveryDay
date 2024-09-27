execute_process(
    COMMAND ${CMAKE_COMMAND} -Dtext=hello -P 输出变量.cmake
    COMMAND ${CMAKE_COMMAND} -Dtext=world -P 输出变量.cmake
    COMMAND ${CMAKE_COMMAND} -E echo hello
    COMMAND ${CMAKE_COMMAND} -E echo world
    COMMAND_ECHO STDOUT
) # 输出：
# '.../cmake' '-Dtext=hello' '-P' '输出变量.cmake'
# '.../cmake' '-Dtext=world' '-P' '输出变量.cmake'
# '.../cmake' '-E' 'echo' 'hello'
# '.../cmake' '-E' 'echo' 'world'
# world
# world
# hello